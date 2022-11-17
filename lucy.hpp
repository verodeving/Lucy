#pragma once
#if lucy_major_version == 0 and lucy_middle_version == 0 and lucy_minor_version == 1
#if defined(lucy_mac)
#include <Dependencies/macos/Internal.hpp>

MTL::Device* __device_;

MTL::Library* __library_;

MTL::ComputePipelineState* __compute_pipeline_state_;

MTL::CommandQueue* __command_queue_;

MTL::ComputeCommandEncoder* __compute_command_encoder_;

class [[nodiscard]] __View_ : public MTK::ViewDelegate
{
    MTL::Size __all_threads_;
    
    static consteval MTL::Size __threads_()
    {
        return {16ul, 16ul, 1ul};
    }
public:
    inline __View_(){}

    inline __View_(MTK::View* __view_)
    {
        if(__device_)
            if((__library_ = __device_->newDefaultLibrary()))
            {
                NS::Error** __error_ = nullptr;
                if((__compute_pipeline_state_ = __device_->newComputePipelineState(__library_->newFunction(NS::String::string("render", NS::StringEncoding::UTF8StringEncoding)), __error_)))
                    if((__command_queue_ = __device_->newCommandQueue()))
                    {
                        MTL::CommandBuffer* __command_buffer_ = __command_queue_->commandBuffer();
                        if(__command_buffer_)
                        {
                            const MTL::Drawable* __drawable_ = __view_->currentDrawable();
                            if(__drawable_)
                            {
                                 __command_buffer_->presentDrawable(__drawable_);
                                 __compute_command_encoder_ = __command_buffer_->computeCommandEncoder();
                                 if(__compute_command_encoder_)
                                 {
                                    const MTL::Texture* __texture_ = __drawable_->texture();
                                    if(__texture_)
                                    {
                                        __all_threads_ = MTL::Size::Make(__texture_->width(), __texture_->height(), 1ul);
                                        __compute_command_encoder_->setComputePipelineState(__compute_pipeline_state_);
                                        __compute_command_encoder_->setTexture(__texture_, 0ul);
                                        __compute_command_encoder_->dispatchThreads(__all_threads_, __threads_());
                                        __compute_command_encoder_->endEncoding();
                                        __command_buffer_->commit();
                                    }
                                 }
                            }
                        }
                    }
            }
    }

    inline void drawInMTKView(MTK::View* __view_) override
    {
        MTL::CommandBuffer* __command_buffer_ = __command_queue_->commandBuffer();
        if(__command_buffer_)
        {
            const MTL::Drawable* __drawable_ = __view_->currentDrawable();
            if(__drawable_)
            {
                __command_buffer_->presentDrawable(__drawable_);
                __compute_command_encoder_ = __command_buffer_->computeCommandEncoder();
                if(__compute_command_encoder_)
                {
                    __compute_command_encoder_->setComputePipelineState(__compute_pipeline_state_);
                    __compute_command_encoder_->setTexture(__drawable_->texture(), 0ul);
                    __compute_command_encoder_->dispatchThreadgroups(__all_threads_, __threads_());
                    __compute_command_encoder_->endEncoding();
                    __command_buffer_->commit();
                }  
            }
        }
    }
};

class [[nodiscard]] __Application_ : public NS::ApplicationDelegate
{
    NS::Window* __window_;

    MTK::View* __view_;

    __View_* __m_view_;
public:
    inline ~__Application_() override
    {
        __command_queue_->release();
        __compute_pipeline_state_->release();
        __library_->release();
        delete __m_view_;
        __view_->release();
        __device_->release();
        __window_->release();
    }

    inline void applicationDidFinishLaunching(NS::Notification*) override
    {
        const CGRect frame = NS::Screen::mainScreen()->frame();
        __window_ = NS::Window::alloc()->init(frame, NS::WindowStyleMaskClosable | NS::WindowStyleMaskTitled | NS::WindowStyleMaskResizable, NS::BackingStoreBuffered, false);
        __window_->setTitle(NS::String::string(NS::ProcessInfo::processInfo()->processName()->utf8String(), NS::StringEncoding::UTF8StringEncoding));
        __window_->cascadeTopLeftFromPoint({20, 20});
        __window_->makeKeyAndOrderFront(nullptr);
        __device_ = MTL::CreateSystemDefaultDevice();
        __view_ = MTK::View::alloc()->init(frame, __device_);
        __window_->setContentView(__view_);
        __view_->setFramebufferOnly(true);
        __view_->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm);
        __view_->setPreferredFramesPerSecond(NS::Screen::mainScreen()->maximumFramesPerSecond());
        __m_view_ = new __View_(__view_);
        __view_->setDelegate(__m_view_);
    }
};

inline void __start_()
{
    NS::AutoreleasePool* __autorelease_pool_ = NS::AutoreleasePool::alloc()->init();
    NS::Application* __application_ = NS::Application::sharedApplication();
    __Application_ __m_application_;
    __application_->setDelegate(&__m_application_);
    __application_->run();
    __autorelease_pool_->release();
}

#endif
#endif