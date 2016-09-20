// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalBackgroundViewModule.h"
#include "ModalBackgroundController.h"
#include "ModalBackgroundAggregateView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace View
        {
			void ModalBackgroundViewModule::Register(const TContainerBuilder& builder)
			{
				ASSERT_UI_THREAD
				builder->registerType<ModalBackgroundAggregateView>().as<Modality::View::IModalBackgroundView>().singleInstance();
			}
        }
    }
}
