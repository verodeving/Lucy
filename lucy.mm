#if lucy_major_version == 0 and lucy_middle_version == 0 and lucy_minor_version == 1
#include <lucy.hpp>
#include <MetalKit/MetalKit.h>
#if defined(lucy_mac)
#include <AppKit/AppKit.h>

@interface Renderer : NSObject<MTKViewDelegate>
-(nonnull instancetype) initWithView: (nonnull MTKView*) __view_;
@end

@interface Renderer()
{
    id<MTLCommandQueue> __command_queue_;

    id<MTLComputePipelineState> __compute_pipeline_state_;

    MTLSize __size_;
}
@end

@implementation Renderer
-(nonnull instancetype) initWithView: (nonnull MTKView*) __view_
{
    if(self = [super init])
    {
        [__view_ setPreferredFramesPerSecond: [NSScreen mainScreen].maximumFramesPerSecond];
        __size_ = MTLSizeMake(1ul, 1ul, 1ul);
        __device_ = __view_.device;
        __library_ = [__device_ newDefaultLibrary];
        __command_queue_ = [__device_ newCommandQueue];
        __compute_pipeline_state_ = [__device_ newComputePipelineStateWithFunction: [__library_ newFunctionWithName: @"render"] error: nil];
        id<MTLCommandBuffer> __command_buffer_ = [__command_queue_ commandBuffer];
        [__command_buffer_ presentDrawable: __view_.currentDrawable];
        __compute_command_encoder_ = [__command_buffer_ computeCommandEncoder];
        //first_frame
        [__compute_command_encoder_ endEncoding];
        [__command_buffer_ commit];
    }
    return self;
}

-(void) drawInMTKView: (nonnull MTKView*) __view_
{
    id<MTLCommandBuffer> __command_buffer_ = [__command_queue_ commandBuffer];
    [__command_buffer_ presentDrawable: __view_.currentDrawable];
    __compute_command_encoder_ = [__command_buffer_ computeCommandEncoder];
    //update_frame
    [__compute_command_encoder_ endEncoding];
    [__command_buffer_ commit];
}

-(void) mtkView: (nonnull MTKView*) __view_ drawableSizeWillChange: (CGSize) __cgsize_
{

}
@end

@interface ViewController : NSViewController
{
    MTKView* __view_;

    Renderer* __renderer_;
}
@end

@implementation ViewController
-(MTKView*) mtkView
{
    return __view_;
}

-(void) viewDidLoad
{
    [super viewDidLoad];
    __renderer_ = [[Renderer alloc] initWithView: __view_];
    __view_.delegate = __renderer_;
}
@end

@interface AppDelegate : NSObject<NSApplicationDelegate, NSWindowDelegate>
{
    NSWindow* __window_;

    ViewController* __controller_;
}
@end

@implementation AppDelegate
-(id) init
{
    if(self = [super init])
    {
        NSRect __rect_ = [[NSScreen mainScreen] frame];
        __controller_ = [[ViewController alloc] init];
        __window_ = [[NSWindow alloc] initWithContentRect: __rect_ styleMask: NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable backing: NSBackingStoreBuffered defer: NO];
        MTKView* __view_ = [[MTKView alloc] initWithFrame: __rect_ device: MTLCreateSystemDefaultDevice()];
        __controller_.view = __view_;
        [__window_ setContentView: __view_];
        [__controller_ viewDidLoad];
    }
    return self;
}

-(void) applicationWillFinishLaunching: (NSNotification*) notification
{
    __window_.title = NSProcessInfo.processInfo.processName;
    [__window_ cascadeTopLeftFromPoint: NSMakePoint(20, 20)];
    [__window_ makeKeyAndOrderFront: self];
}

-(BOOL) applicationShouldTerminateAfterLastWindowClosed: (NSApplication*) sender
{
    return YES;
}
@end

int main()
{
    @autoreleasepool
    {
        NSApplication* __app_ = NSApplication.sharedApplication;
        __app_.delegate = [AppDelegate new];
        [__app_ run];
    }
}
#endif
#endif