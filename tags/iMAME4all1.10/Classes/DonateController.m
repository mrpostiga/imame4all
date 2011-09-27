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
 
#import "DonateController.h"
#import "EmulatorController.h"
#include <stdio.h>

@implementation DonateController

@synthesize bIsDismissed;

- (id)init {

    if (self = [super init]) {

        bIsDismissed = NO;
        navBar = nil;
        aWebView = nil;
    }

    return self;

}

- (void)loadView {

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
    
   navBar = [ [ UINavigationBar alloc ] initWithFrame: CGRectMake(rect.origin.x, rect.origin.y, rect.size.width, 45.0f)];
   [ navBar setDelegate: self ];

   UINavigationItem *item = [[ UINavigationItem alloc ] initWithTitle:@"Donate" ];
   
   UIBarButtonItem *backButton = [[[UIBarButtonItem alloc] initWithTitle:@"Quit" style:UIBarButtonItemStyleBordered target:/*[self parentViewController]*/self action:  @selector(mydone:) ] autorelease];
   //UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"Quit2" style:UIBarButtonItemStyleBordered target:[self parentViewController]   action:  @selector(done:) ];
   
   item.rightBarButtonItem = backButton;
  
   /*  
   UILabel *bigLabel = [[UILabel alloc] init];
   bigLabel.text = @"I am BIG";
   bigLabel.font = [UIFont fontWithName:@"Arial" size: 22.0];
   [bigLabel sizeToFit];
   item.titleView = bigLabel;
   [bigLabel release];
   */
   [ navBar pushNavigationItem: item  animated:YES];
     
   [ self.view addSubview: navBar ];
    

   aWebView = [ [ UIWebView alloc ] initWithFrame: CGRectMake(rect.origin.x, rect.origin.y + 45.0f, rect.size.width,rect.size.height - 45.0f )];

   aWebView.scalesPageToFit = YES;

   aWebView.autoresizesSubviews = YES;
   aWebView.autoresizingMask=(UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth);

   //set the web view delegates for the web view to be itself
   [aWebView setDelegate:self];

   
   //Set the URL to go to for your UIWebView
   NSString *urlAddress = @"https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=seleuco%2enicator%40gmail%2ecom&lc=US&item_name=Seleuco%20Nicator&item_number=ixxxx4all&no_note=0&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donateCC_LG%2egif%3aNonHostedGuest";
                        

   //Create a URL object.
   NSURL *url = [NSURL URLWithString:urlAddress];

   //URL Requst Object
   NSURLRequest *requestObj = [NSURLRequest requestWithURL:url];
   
   
   //load the URL into the web view.
   [aWebView loadRequest:requestObj];
      
   /*
   NSString *HTMLData = [[NSString alloc] initWithContentsOfFile: @"/Applications/iXpectrum.app/donate.html"];
      
   NSURL *aURL = [NSURL fileURLWithPath:@"/Applications/iXpectrum.app/"];
      
   [aWebView loadHTMLString:HTMLData baseURL: aURL];
   
   [HTMLData release];
   */
   
   [ self.view addSubview: aWebView ];

}


-(void)mydone:(id)sender{
   //[aWebView setDelegate:nil];
    if ([aWebView isLoading])
        [aWebView stopLoading];
   [self dismissModalViewControllerAnimated:YES];
   
   EmulatorController *eC = (EmulatorController *)[self parentViewController];	
   [eC endMenu];
   
}


-(void)viewDidLoad{	
   
   
   	        UIAlertView *thksAlert = [[UIAlertView alloc] initWithTitle:@"Thanks for your support!" 
															  
 
 message:[NSString stringWithFormat: @"All my projects come to you free of charge and ad-free, because that's what i like my work to be, but if you want to thank me for my effort or colaborate in future developments, feel free to donate me for some beers :)"]
														 
															 delegate:self 
													cancelButtonTitle:@"OK" 
													otherButtonTitles: nil];
	
	       [thksAlert show];
	       [thksAlert release];
     
}

- (void)webViewDidStartLoad:(UIWebView *)webView{
    //[navBar topItem].title = webView.request.URL.absoluteString;
     //[self retain];    
}

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType{
    if(navBar!=nil && [navBar topItem]!= nil)
      [navBar topItem].title = @"Wait... Loading!";
   return YES;
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error{
    if(navBar!=nil && [navBar topItem]!= nil)
      [navBar topItem].title = @"Error";
    if(error!=nil && error.code != NSURLErrorCancelled)
    {
		UIAlertView *connectionAlert = [[UIAlertView alloc] initWithTitle:@"Connection Failed!" 
																  message:[NSString stringWithFormat:@"There is no internet connection. Connect to the internet and try again. Error:%@",[error localizedDescription]] 
																 delegate:self 
														cancelButtonTitle:@"OK" 
														otherButtonTitles: nil];
		
		[connectionAlert show];
		[connectionAlert release];
	}
    //[self release];
    
}

- (void)webViewDidFinishLoad:(UIWebView *)webView{

   if(navBar!=nil && webView!=nil)
   {
       if([navBar topItem]!= nil && webView.request!=nil)
         [navBar topItem].title = webView.request.URL.absoluteString;
   }  
   //[self release];   
}


-(BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
       //return (interfaceOrientation == UIInterfaceOrientationPortrait);
       return YES;
}

- (void)didReceiveMemoryWarning {
	//[super didReceiveMemoryWarning];
}


- (void)dealloc {
   
  
    if(navBar!=nil)
    {
       [navBar  release];
       navBar = nil;
    }  
    
    if(aWebView!=nil)
    {
       //[aWebView stopLoading]; 
       [aWebView setDelegate:nil];       
       [aWebView release];
       aWebView = nil;
    }   
     
	[super dealloc];
}

@end
