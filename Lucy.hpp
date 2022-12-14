#pragma once
#if lucy_major_version == 0 and lucy_middle_version == 0 and lucy_minor_version == 1
#if defined(lucy_mac)
#include <Game.hpp>
#include <Dependencies/macos/Internal.hpp>

inline MTL::Device* __device_;

inline MTL::Library* __library_;

inline MTL::ComputePipelineState* __compute_pipeline_state_;

inline MTL::CommandQueue* __command_queue_;

inline MTL::ComputeCommandEncoder* __compute_command_encoder_;

inline MTL::Size __all_threads_;
    
[[nodiscard]] inline consteval MTL::Size __threads_()
{
    return {32ul, 16ul, 1ul};
}

class [[nodiscard]] __View_ : public MTK::ViewDelegate
{
    bool __ok_ = false;
public:
    inline __View_(){}

    inline __View_(MTK::View* __view_)
    {
        if(__device_)
            if(__device_->supportsFamily(MTL::GPUFamilyMetal3))
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
                                            Lucy::Game::Start();
                                            __compute_command_encoder_->endEncoding();
                                            __command_buffer_->presentDrawable(__drawable_);
                                            __command_buffer_->commit();
                                            __ok_ = true;
                                        }
                                     }
                                }
                            }
                        }
                }
    }

    [[nodiscard]] inline bool __get_ok_() const
    {
        return __ok_;
    }

    inline void drawInMTKView(MTK::View* __view_) override
    {
        MTL::CommandBuffer* __command_buffer_ = __command_queue_->commandBuffer();
        const MTL::Drawable* __drawable_ = __view_->currentDrawable();
        __compute_command_encoder_ = __command_buffer_->computeCommandEncoder();
        __compute_command_encoder_->setComputePipelineState(__compute_pipeline_state_);
        __compute_command_encoder_->setTexture(__drawable_->texture(), 0ul);
        __compute_command_encoder_->dispatchThreadgroups(__all_threads_, __threads_());
        Lucy::Game::Update();
        __compute_command_encoder_->endEncoding();
        __command_buffer_->presentDrawable(__drawable_);
        __command_buffer_->commit();
    }
};

class [[nodiscard]] __Application_ : public NS::ApplicationDelegate
{
    NS::Window* __window_;

    MTK::View* __view_;

    __View_ __m_view_;
public:
    inline ~__Application_() override
    {
        MTL::CommandBuffer* __command_buffer_ = __command_queue_->commandBuffer();
        const MTL::Drawable* __drawable_ = __view_->currentDrawable();
        __compute_command_encoder_ = __command_buffer_->computeCommandEncoder();
        __compute_command_encoder_->setComputePipelineState(__compute_pipeline_state_);
        __compute_command_encoder_->setTexture(__drawable_->texture(), 0ul);
        __compute_command_encoder_->dispatchThreadgroups(__all_threads_, __threads_());
        Lucy::Game::Finish();
        __compute_command_encoder_->endEncoding();
        __command_buffer_->presentDrawable(__drawable_);
        __command_buffer_->commit();
        __command_queue_->release();
        __compute_pipeline_state_->release();
        __library_->release();
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
        __view_->setFramebufferOnly(false);
        __view_->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm);
        __view_->setPreferredFramesPerSecond(NS::Screen::mainScreen()->maximumFramesPerSecond());
        __m_view_ = __View_(__view_);
        if(__m_view_.__get_ok_())
            __view_->setDelegate(&__m_view_);
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