//
//  ISHPermissionRequest.h
//  ISHPermissionKit
//
//  Created by Felix Lamouroux on 25.06.14.
//  Copyright (c) 2014 iosphere GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ISHPermissionKit/ISHPermissionCategory.h>

typedef NS_ENUM(NSUInteger, ISHPermissionState) {
    ISHPermissionStateUnknown = 0,
    ISHPermissionStateUnsupported = 1,
    ISHPermissionStateNeverAsked = 100,
    ISHPermissionStateAskAgain = 101,
    ISHPermissionStateDontAsk = 110,
    ISHPermissionStateDenied = 403,
    ISHPermissionStateAuthorized = 200,
};

@class ISHPermissionRequest;

typedef void (^ISHPermissionRequestCompletionBlock)(ISHPermissionRequest *request, ISHPermissionState state, NSError *error);


@interface ISHPermissionRequest : NSObject
@property ISHPermissionCategory permissionCategory;

- (ISHPermissionState)permissionState;
- (void)requestUserPermissionWithCompletionBlock:(ISHPermissionRequestCompletionBlock)completion;
@end

static inline NSString *ISHStringFromPermissionState(ISHPermissionState state) {
    switch (state) {
        case ISHPermissionStateUnknown:
            return @"ISHPermissionStateUnknown";
        case ISHPermissionStateNeverAsked:
            return @"ISHPermissionStateNeverAsked";
        case ISHPermissionStateAskAgain:
            return @"ISHPermissionStateAskAgain";
        case ISHPermissionStateDontAsk:
            return @"ISHPermissionStateDontAsk";
        case ISHPermissionStateDenied:
            return @"ISHPermissionStateDenied";
        case ISHPermissionStateAuthorized:
            return @"ISHPermissionStateAuthorized";

    }
}

static inline BOOL ISHPermissionStateAllowsUserPrompt(ISHPermissionState state) {
    return (state != ISHPermissionStateDenied) && (state != ISHPermissionStateAuthorized) && (state != ISHPermissionStateDontAsk) && (state != ISHPermissionStateUnsupported);
}

@interface ISHPermissionRequest (Subclasses)
// these interfaces are available to subclasses, there should be no need to override these.
- (ISHPermissionState)internalPermissionState;
- (void)setInternalPermissionState:(ISHPermissionState)state;
@end
