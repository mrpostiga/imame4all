/*
 * This file is part of iMAME4all.
 *
 * Copyright (C) 2011-2013 David Valdeita (Seleuco)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses>.
 *
 * Linking iMAME4all statically or dynamically with other modules is
 * making a combined work based on iMAME4all. Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * In addition, as a special exception, the copyright holders of iMAME4all
 * give you permission to combine iMAME4all with free software programs
 * or libraries that are released under the GNU LGPL and with code included
 * in the standard release of MAME under the MAME License (or modified
 * versions of such code, with unchanged license). You may copy and
 * distribute such a system following the terms of the GNU GPL for iMAME4all
 * and the licenses of the other code concerned, provided that you include
 * the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of iMAME4all are not
 * obligated to grant this special exception for their modified versions; it
 * is their choice whether to do so. The GNU General Public License
 * gives permission to release a modified version without this exception;
 * this exception also makes it possible to release a modified version
 * which carries forward this exception.
 *
 * iMAME4all is dual-licensed: Alternatively, you can license iMAME4all
 * under a MAME license, as set out in http://mamedev.org/
 */
 
#import "DonateController.h"
#import "EmulatorController.h"
#import "Helper.h"
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

	UIViewController *pctrl = self_parentViewController;
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
   
   EmulatorController *eC = (EmulatorController *)self_parentViewController;
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
