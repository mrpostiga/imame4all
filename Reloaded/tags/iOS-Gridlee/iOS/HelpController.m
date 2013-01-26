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

#import "HelpController.h"
#import "Globals.h"

@implementation HelpController


- (id)init {

    if (self = [super init]) {
        aWebView  = nil;
    }

    return self;
}

- (void)loadView {
       
	UIView *view= [[UIView alloc] initWithFrame:[[UIScreen mainScreen] applicationFrame]];
	self.view = view;
	[view release];
    
    self.title = @"Help";
    self.view.backgroundColor = [UIColor whiteColor];
    self.view.autoresizesSubviews = TRUE;
        
    aWebView =[ [ UIWebView alloc ] initWithFrame: view.frame];
    
    //aWebView.scalesPageToFit = YES;
    
    aWebView.autoresizingMask = (UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight);
    
    [ self.view addSubview: aWebView ];
}

-(void)viewDidLoad{	

}

-(void)viewWillAppear:(BOOL)animated
{
    aWebView.delegate = self;
    
    [self loadHTML];
}

-(void)viewWillDisappear:(BOOL)animated
{
    [aWebView stopLoading];
    aWebView.delegate = nil;
}

-(BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    //   return (interfaceOrientation == UIInterfaceOrientationPortrait);
    return YES;
    //return NO;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
    
    //[self loadHTML];
    //[aWebView reload];    
}

- (void)didReceiveMemoryWarning {
	[super didReceiveMemoryWarning];
}

 
- (void)dealloc {
    
    aWebView.delegate = nil;
    [aWebView release];

	[super dealloc];
}

-(BOOL) webView:(UIWebView *)inWeb shouldStartLoadWithRequest:(NSURLRequest *)inRequest navigationType:(UIWebViewNavigationType)inType {
    if ( inType == UIWebViewNavigationTypeLinkClicked ) {
        [[UIApplication sharedApplication] openURL:[inRequest URL]];
        return NO;
    }
    
    return YES;
}

- (void)loadHTML{
    NSString *HTMLData = [[NSString alloc] initWithContentsOfFile: [NSString stringWithUTF8String:get_resource_path("help.html")] encoding:NSUTF8StringEncoding error:nil];
    
    NSURL *aURL = [NSURL fileURLWithPath:[NSString stringWithUTF8String:get_resource_path("")]];
    
    [aWebView loadHTMLString:HTMLData baseURL: aURL];
    
    [HTMLData release];
}

@end