//
//  DAVRequest.h
//  DAVKit
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#import "DAVBaseRequest.h"

@protocol DAVRequestDelegate;

/* codes returned are HTTP status codes */
extern NSString *const DAVClientErrorDomain;

@interface DAVRequest : DAVBaseRequest {
  @private
	NSString *_path;
	NSURLConnection *_connection;
	NSMutableData *_data;
	BOOL _done, _cancelled;
	BOOL _executing;
}

#if __has_feature(objc_arc)
@property (strong, readonly) NSString *path;
#else
@property (retain, readonly) NSString *path;
#endif

#if __has_feature(objc_arc_weak)
@property (weak) __weak id < DAVRequestDelegate > delegate;
#elif __has_feature(objc_arc)
@property (unsafe_unretained) __weak id < DAVRequestDelegate > delegate;
#else
@property (assign) __weak id < DAVRequestDelegate > delegate;
#endif

- (id)initWithPath:(NSString *)aPath;

- (NSURL *)concatenatedURLWithPath:(NSString *)aPath;

/* must be overriden by subclasses */
- (NSURLRequest *)request;

/* optional override */
- (id)resultForData:(NSData *)data;

@end


@protocol DAVRequestDelegate < NSObject >

// The error can be a NSURLConnection error or a WebDAV error
- (void)request:(DAVRequest *)aRequest didFailWithError:(NSError *)error;

// The resulting object varies depending on the request type
- (void)request:(DAVRequest *)aRequest didSucceedWithResult:(id)result;

@optional

- (void)requestDidBegin:(DAVRequest *)aRequest;

@end
