// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalBackgroundNativeViewModule.h"
#include "RenderableFilters.h"
#include "RenderingModule.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "ModalBackgroundNativeView.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "GlBufferPool.h"
#include "VertexLayoutPool.h"
#include "VertexBindingPool.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace SdkModel
        {
			void ModalBackgroundNativeViewModule::Register(const TContainerBuilder& builder)
			{
				builder->registerType<ModalBackgroundNativeView>().singleInstance();
			}
        }
    }
}
