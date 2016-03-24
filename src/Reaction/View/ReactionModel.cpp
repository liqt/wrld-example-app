// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ReactionModel.h"
#include "MathFunc.h"
#include "IIdentity.h"
#include "IReactionControllerModel.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            ReactionModel::ReactionModel(IReactionControllerModel& reactionControllerModel,
                                         const std::vector<OpenableControl::View::IOpenableControlViewModel*>& openables,
                                         const std::vector<ScreenControl::View::IScreenControlViewModel*>& reactors)
                : m_reactionControllerModel(reactionControllerModel)
                , m_openables(openables)
                , m_reactors(reactors)
                , m_pMenuOpenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<ReactionModel, OpenableControl::View::IOpenableControlViewModel&, float>))(this, &ReactionModel::MenuOpenStateChangeHandler))
            {
                for(std::vector<OpenableControl::View::IOpenableControlViewModel*>::iterator it = m_openables.begin();
                        it != m_openables.end();
                        ++ it)
                {
                    OpenableControl::View::IOpenableControlViewModel& openable = **it;
                    openable.InsertOpenStateChangedCallback(*m_pMenuOpenStateChangedCallback);
                }
            }

            ReactionModel::~ReactionModel()
            {
                for(std::vector<OpenableControl::View::IOpenableControlViewModel*>::iterator it = m_openables.begin();
                        it != m_openables.end();
                        ++ it)
                {
                    OpenableControl::View::IOpenableControlViewModel& openable = **it;
                    openable.RemoveOpenStateChangedCallback(*m_pMenuOpenStateChangedCallback);
                }

                Eegeo_DELETE m_pMenuOpenStateChangedCallback;
            }

            void ReactionModel::AddIgnoredMenuIdentity(Eegeo::Helpers::TIdentity identity)
            {
                m_ignoredMenuIdentities.push_back(identity);
            }

            void ReactionModel::RemoveIgnoredMenuIdentity(Eegeo::Helpers::TIdentity identity)
            {
                std::vector<Eegeo::Helpers::TIdentity>::iterator result = std::find(m_ignoredMenuIdentities.begin(), m_ignoredMenuIdentities.end(), identity);

                m_ignoredMenuIdentities.erase(result);
            }

            void ReactionModel::UpdateOnScreenStatesInReactionToMenuOpenStateChange(OpenableControl::View::IOpenableControlViewModel& changingViewModel, float openState)
            {
                for(std::vector<ScreenControl::View::IScreenControlViewModel*>::const_iterator it = m_reactors.begin();
                        it != m_reactors.end();
                        ++ it)
                {
                    ScreenControl::View::IScreenControlViewModel& reactor = **it;

                    if(reactor != changingViewModel)
                    {
                        reactor.UpdateOnScreenState(1.f - openState);
                    }
                }
            }

            void ReactionModel::MenuOpenStateChangeHandler(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState)
            {
                Eegeo::Helpers::TIdentity identity = viewModel.GetIdentity();

                if (std::find(m_ignoredMenuIdentities.begin(), m_ignoredMenuIdentities.end(), identity) != m_ignoredMenuIdentities.end())
                {
                    return;
                }
                
                if(m_reactionControllerModel.HasModalControl(viewModel.GetIdentity()))
                {
                    UpdateOnScreenStatesInReactionToMenuOpenStateChange(viewModel, openState);
                }
            }
        }
    }
}
