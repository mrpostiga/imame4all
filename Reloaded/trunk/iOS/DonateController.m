/*
 * This file is part of MAME4iOS.
 *
 * Copyright (C) 2012 David Valdeita (Seleuco)
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
#import "Globals.h"
#import "EmulatorController.h"

@implementation DonateController


- (id)init {
    
    if (self = [super init]) {
        aWebView = nil;
    }
    
    return self;
}

- (void)loadView {
	
	UIView *view= [[UIView alloc] initWithFrame:[[UIScreen mainScreen] applicationFrame]];
	self.view = view;
	[view release];
    self.view.backgroundColor = [UIColor whiteColor];
    
    self.title = @"Donate";
    
    aWebView = [ [ UIWebView alloc ] initWithFrame: self.view.frame];
    
    aWebView.scalesPageToFit = YES;
    
    aWebView.autoresizesSubviews = YES;
    aWebView.autoresizingMask=(UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth);
    
    [ self.view addSubview: aWebView ];
}

-(void)viewDidLoad{	
   
    
    UIAlertView *thksAlert = [[UIAlertView alloc] initWithTitle:@"Thanks for your support!"
                              
                              
                                                        message:[NSString stringWithFormat: @"I am releasing everything for free, in keeping with the licensing MAME terms, which is free for non-commercial use only. This is strictly something I made because I wanted to play with it and have the skills to make it so. That said, if you are thinking on ways to support my development I suggest you to check my support page of other free works for the community."]
                              
                                                       delegate:self
                                              cancelButtonTitle:@"OK" 
                                              otherButtonTitles: nil];
	
    [thksAlert show];
    [thksAlert release];
   
}

- (void)viewWillAppear:(BOOL)animated{
    
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
}

-(void)viewWillDisappear:(BOOL)animated{
    [aWebView stopLoading];
    [aWebView setDelegate:nil];
    
}

/////

- (void)webViewDidStartLoad:(UIWebView *)webView{
    
}

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType{

   self.title = @"Wait... Loading!";
   return YES;
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error{
    self.title = @"Error";
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
}

- (void)webViewDidFinishLoad:(UIWebView *)webView{
    
    if(webView!=nil)
    {
        if(webView.request!=nil)
            self.title = webView.request.URL.absoluteString;
    }
}


-(BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    //return (interfaceOrientation == UIInterfaceOrientationPortrait);
    return YES;
}

- (void)didReceiveMemoryWarning {
	//[super didReceiveMemoryWarning];
}


- (void)dealloc {
    
    [aWebView release];
    
	[super dealloc];
}

@end
