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

#import "HelpController.h"
#include <stdio.h>
#import "Helper.h"


@implementation HelpController

@synthesize bIsDismissed;

- (id)init {

    if (self = [super init]) {

        bIsDismissed = NO;
    }

    return self;

}

- (void)loadView {
   

	//struct CGRect rect = [[UIScreen mainScreen] bounds];
	UIViewController *pctrl = [self parentViewController];		
	struct CGRect rect = pctrl.view.frame;//[[UIScreen mainScreen] bounds];
	rect.origin.x = rect.origin.y = 0.0f;	
	if(pctrl.interfaceOrientation==UIInterfaceOrientationLandscapeLeft 
	||pctrl.interfaceOrientation==UIInterfaceOrientationLandscapeRight )
	{
	     int tmp = rect.size.width;
	     rect.size.width = rect.size.height; 
	     rect.size.height = tmp;	     
	}

	UIView *view= [[UIView alloc] initWithFrame:rect];
	self.view = view;
	[view release];
    self.view.backgroundColor = [UIColor whiteColor];
    
   UINavigationBar *navBar = [ [ UINavigationBar alloc ] initWithFrame: CGRectMake(rect.origin.x, rect.origin.y, rect.size.width, 45.0f)];
   [ navBar setDelegate: self ];

   UINavigationItem *item = [[ UINavigationItem alloc ] initWithTitle:@"Credits & Help" ];
   UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"OK" style:UIBarButtonItemStyleBordered target:[self parentViewController]   action:  @selector(done:) ];
   item.rightBarButtonItem = backButton;
   [backButton release];
   [ navBar pushNavigationItem: item  animated:YES];
     
   [ self.view addSubview: navBar ];
   [navBar release];
    
    
    FILE *file;
    char buffer[262144], buf[1024];

    UITextView *textView = [ [ UITextView alloc ] initWithFrame: CGRectMake(rect.origin.x, rect.origin.y + 45.0f, rect.size.width,rect.size.height - 45.0f )];
//        [ textView setTextSize: 12 ];

    textView.font = [UIFont fontWithName:@"Courier New" size:14.0];


    textView.editable = NO;

    file = fopen(get_resource_path("readme.txt"), "r");

    if (!file) 
    {        
            textView.textColor =  [UIColor redColor];            
            [ textView setText: @"ERROR: File not found" ];
            
    } else 
    {
            buffer[0] = 0;
            while((fgets(buf, sizeof(buf), file))!=NULL) {
                strlcat(buffer, buf, sizeof(buffer));
            }
            fclose(file);

            [ textView setText: [ [[ NSString alloc ] initWithCString: buffer ] autorelease]];
    }

    [ self.view addSubview: textView ];
    [textView release];
    
    
}

-(void)viewDidLoad{	

}



-(BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
       //return (interfaceOrientation == UIInterfaceOrientationPortrait);       
       return YES;
}

- (void)didReceiveMemoryWarning {
	[super didReceiveMemoryWarning];
}

 
- (void)dealloc {
       
	[super dealloc];
}

@end