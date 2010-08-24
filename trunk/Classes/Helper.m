/*
 * This file is part of iMAME4all.
 *
 * Copyright (C) 2010 David Valdeita (Seleuco)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * In addition, as a special exception, Seleuco
 * gives permission to link the code of this program with
 * the MAME library (or with modified versions of MAME that use the
 * same license as MAME), and distribute linked combinations including
 * the two.  You must obey the GNU General Public License in all
 * respects for all of the code used other than MAME.  If you modify
 * this file, you may extend this exception to your version of the
 * file, but you are not obligated to do so.  If you do not wish to
 * do so, delete this exception statement from your version.
 */

#include <sys/types.h>
#include <sys/sysctl.h>

#import "Helper.h"

#import "BTDevice.h"
#import "BTInquiryViewController.h"

#import <btstack/btstack.h>
#import <btstack/run_loop.h>
#import <btstack/hci_cmds.h>

unsigned long btUsed = 0;
bool btOK = false;
bool initLoop = false;
BTDevice *device;
uint16_t wiiMoteConHandle = 0;
BTInquiryViewController *inqViewControl;
extern int iphone_menu;
extern int iphone_is_landscape;
extern int iOS_exitGame;
  
void packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size){
        bd_addr_t event_addr;

        switch (packet_type) {

                case L2CAP_DATA_PACKET:
                        if (packet[0] == 0xa1 && packet[1] == 0x31)
                        {
/*
  0 	 0x01 	 D-Pad Left 	 Two
  1 	0x02 	D-Pad Right 	One
  2 	0x04 	D-Pad Down 	B
  3 	0x08 	D-Pad Up 	A
  4 	0x10 	Plus 	Minus
  5 	0x20 	Other uses 	Other uses
  6 	0x40 	Other uses 	Other uses
  7 	0x80 	Unknown 	Home
*/
                                gp2x_pad_status = 0;
                                if(packet[2] & 0x01) // left
                                {
                                  gp2x_pad_status |= GP2X_DOWN;
                                  //NSLog(@"Wii_DOWN");
                                }
                                if(packet[2] & 0x02) // right
                                {
                                  gp2x_pad_status |= GP2X_UP;
                                  //NSLog(@"Wii_UP");
                                }                                
                                if(packet[2] & 0x04) // down
                                {
                                  gp2x_pad_status |= GP2X_RIGHT;
                                  //NSLog(@"Wii_RIGTH");
                                }
                                if(packet[2] & 0x08) // up
                                {
                                  gp2x_pad_status |= GP2X_LEFT;
                                  //NSLog(@"Wii_LEFT");
                                }
                                if(packet[2] & 0x10)
                                {
                                  gp2x_pad_status |= GP2X_START;
                                  //NSLog(@"Wii_START");
                                }
                                if(packet[3] & 0x01)
                                {
                                  gp2x_pad_status |= GP2X_B;
                                  //NSLog(@"Wii_B");
                                }
                                if(packet[3] & 0x02)
                                {
                                  gp2x_pad_status |= GP2X_X;
                                  //NSLog(@"Wii_X");
                                }
                            
                                if(packet[3] & 0x04)
                                {
                                  gp2x_pad_status |= GP2X_R;                                
                                  //NSLog(@"Wii_L");
                                }
                                if(packet[3] & 0x08)
                                {
                                  gp2x_pad_status |= GP2X_A;
                                  //gp2x_pad_status |= GP2X_R;
                                  //NSLog(@"Wii_R");                                  
                                }
                                if(packet[3] & 0x10)
                                {
                                  gp2x_pad_status |= GP2X_SELECT;
                                  //NSLog(@"Wii_SELECT");                                  
                                }
                                if(packet[3] & 0x80)
                                {
                                  //gp2x_pad_status |= GP2X_R;
                                  //NSLog(@"Wii_R");
                                  iOS_exitGame = 0;
                                  usleep(50000);	 
                                  iOS_exitGame = 1;
                                }
                                
                                                                 
                                //gp2x_pad_x_axis = packet[4];
                                //gp2x_pad_y_axis = packet[5];
                                //gp2x_pad_z_axis = packet[6];
                                
                                //fprintf(stderr, "x: %d y: %d z: %d packet 4 %d 5 %d 6 %d\n", gp2x_pad_x_axis, gp2x_pad_y_axis, gp2x_pad_z_axis, packet[4], packet[5], packet[6]);
                                //fflush(stderr);
                        }
                        break;

                case HCI_EVENT_PACKET:

                        switch (packet[0]){

                                case L2CAP_EVENT_CHANNEL_OPENED:
                                        if (packet[2] == 0) {
                                                // inform about new l2cap connection
                                                bt_flip_addr(event_addr, &packet[3]);
                                                uint16_t psm = READ_BT_16(packet, 11);
                                                uint16_t source_cid = READ_BT_16(packet, 13);
                                                wiiMoteConHandle = READ_BT_16(packet, 9);
                                                NSLog(@"Channel successfully opened: handle 0x%02x, psm 0x%02x, source cid 0x%02x, dest cid 0x%02x",
                                                           wiiMoteConHandle, psm, source_cid,  READ_BT_16(packet, 15));
                                                if (psm == 0x13) {
                                                        // interupt channel openedn succesfully, now open control channel, too.
                                                        bt_send_cmd(&l2cap_create_channel, event_addr, 0x11);
                                                } else {

                                                        // request acceleration data.. probably has to be sent to control channel 0x11 instead of 0x13
                                                        uint8_t setMode31[] = { 0x52, 0x12, 0x00, 0x31 };
                                                        bt_send_l2cap( source_cid, setMode31, sizeof(setMode31));
                                                        uint8_t setLEDs[] = { 0x52, 0x11, 0x10 };
                                                        bt_send_l2cap( source_cid, setLEDs, sizeof(setLEDs));

                                                        btUsed = 1;                                                                                                                                                                          
                                                        [inqViewControl dismissModalViewControllerAnimated:YES];
                                                        iphone_menu = 0;
                                                }
                                        }
                                        break;

                                default:
                                        break;
                        }
                        break;

                default:
                        break;
        }
}

@implementation Helper
 
+ (NSString *)machine
{
  size_t size;
 
  // Set 'oldp' parameter to NULL to get the size of the data
  // returned so we can allocate appropriate amount of space
  sysctlbyname("hw.machine", NULL, &size, NULL, 0); 
 
  // Allocate the space to store name
  char *name = malloc(size);
 
  // Get the platform name
  sysctlbyname("hw.machine", name, &size, NULL, 0);
 
  // Place name into a string
  NSString *machine = [NSString stringWithCString:name];
 
  // Done with this
  free(name);
 
  return machine;
}



+(void) startwiimote:(UIViewController *)controller{

   //if(initLoop)return;

  if(!initLoop)
  {
     run_loop_init(RUN_LOOP_COCOA);
     initLoop = true;
  }   
  if(!btOK )
  {
	  if (bt_open() ){
	      // Alert user?
	  } else {
	      bt_register_packet_handler(packet_handler);
	      btOK = true;
	  }
  }
  
  if (btOK) 
  {
    // create inq controller
    if(inqViewControl==nil)
    {
       inqViewControl = [[BTInquiryViewController alloc] init];
    
	   struct CGRect rect = 
	  // controller.view.frame;
	  // [inqViewControl parentViewController].view.frame;
	  [[UIScreen mainScreen] bounds]; 
	  CGFloat navBarWidht = /*iphone_is_landscape ?*/ rect.size.height /*: rect.size.width*/;     
	  CGFloat navBarHeight = 45;     
	  UINavigationBar *navBar = [ [ UINavigationBar alloc ] initWithFrame: CGRectMake(0, 0, navBarWidht , navBarHeight)];
	  [navBar autorelease];
	  [navBar setDelegate: inqViewControl ];
	   
	   //UINavigationItem *item = [[ UINavigationItem alloc ] initWithTitle:@"WiiMote Device Selector" ];
	   /*
	   UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"Cancel\Stop" style:UIBarButtonItemStyleBordered target:self  action:  @selector(cancelWiiMoteSearch) ];
	   item.rightBarButtonItem = backButton;
	   [backButton release];
	   */
	   //[ navBar pushNavigationItem: item  animated:YES];
	   
   UILabel *navLabel = [[UILabel alloc] initWithFrame:CGRectMake(5,0,navBarWidht, navBarHeight)];
   
   navLabel.autoresizingMask = UIViewAutoresizingFlexibleWidth;
   navLabel.text = @"WiiMote Device Selector";
   navLabel.backgroundColor = [UIColor clearColor];
   navLabel.textColor = [UIColor whiteColor];
   navLabel.font = [UIFont systemFontOfSize: 18];
   navLabel.textAlignment = UITextAlignmentLeft;
   [navBar addSubview:navLabel];
   [navLabel release];
	     
	   [[inqViewControl tableView] setTableHeaderView:navBar];
	   [navBar release];
	    	
	    UITextView *footer = [[UITextView alloc] initWithFrame:CGRectMake(10,00,300,100)];
	    footer.text = @"Make your WiiMote discoverable by pressing the 1+2 buttons at the same time.";
	    footer.textColor = [UIColor blackColor];
	    footer.font = [UIFont fontWithName:@"Arial" size:18];
	
	    footer.backgroundColor = [UIColor whiteColor];
	    footer.autoresizingMask = UIViewAutoresizingFlexibleWidth;
	    footer.editable = false;
	    [[inqViewControl tableView] setTableFooterView:footer];
    }
    
    UIAlertView* downloadAlertView=[[UIAlertView alloc] initWithTitle:nil
	                     message:@"are you sure you search a WiiMote?"
					     delegate:self cancelButtonTitle:nil
	                     otherButtonTitles:@"Yes",@"No",nil];
    [downloadAlertView show];
    [downloadAlertView release];
        
    [controller presentModalViewController:inqViewControl animated:YES];
    
  }

}

+ (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{

  if(buttonIndex == 0 )
  {
     [inqViewControl setDelegate:self];
     [inqViewControl startInquiry];
  }
  else
  {
     [inqViewControl dismissModalViewControllerAnimated:YES];
     iphone_menu = 0;
  }
}

+(void) cancelWiiMoteSearch {        
    [inqViewControl stopInquiry];
}

+(void) deviceChoosen:(BTInquiryViewController *) inqView device:(BTDevice*) selectedDevice{
        NSLog(@"deviceChoosen %@", [device toString]);
}

+ (void) deviceDetected:(BTInquiryViewController *) inqView device:(BTDevice*) selectedDevice {

        NSLog(@"deviceDetected %@", [device toString]);
        if ([selectedDevice name] && [[selectedDevice name] caseInsensitiveCompare:@"Nintendo RVL-CNT-01"] == NSOrderedSame){
                NSLog(@"WiiMote found with address %@", [BTDevice stringForAddress:[selectedDevice address]]);
                device = selectedDevice;
                [inqViewControl stopInquiry];
                [inqViewControl showConnecting:device];

                // connect to device
                [device setConnectionState:kBluetoothConnectionConnecting];
                [[inqViewControl tableView] reloadData];
                bt_send_cmd(&l2cap_create_channel, [device address], 0x13);
        }
}

+ (void) inquiryStopped{
/*
    if (wiiMoteConHandle) {
          bt_send_cmd(&hci_disconnect, wiiMoteConHandle, 0x13); // remote closed connection
          wiiMoteConHandle = 0;
    }
*/
 //   [inqViewControl dismissModalViewControllerAnimated:YES];
    //iphone_menu = 0;

}

+ (void) disconnectDevice:(BTInquiryViewController *) inqView device:(BTDevice*) selectedDevice {
}




@end

