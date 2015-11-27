// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ITwitterFeedTourModule.h"
#include "Types.h"
#include "TwitterFeedTour.h"
#include "Tours.h"
#include "WorldPins.h"
#include "TwitterFeed.h"
#include "TweetStateData.h"
#include "Metrics.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace TourInstances
            {
                namespace TwitterFeed
                {
                    class TwitterFeedTourModule : public ITwitterFeedTourModule, private Eegeo::NonCopyable
                    {
                    private:
                        TwitterFeedTourObserver* m_pTwitterFeedTourObserver;
                        std::map<std::string, TweetStateData> m_tweetStateDataMap;
                    public:
                        TwitterFeedTourModule(Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                              Camera::IToursCameraController& toursCameraController,
                                              ITourService& tourService,
                                              WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                              ITourRepository& tourRepository,
                                              Social::TwitterFeed::ITwitterFeedService& twitterFeedService,
                                              Metrics::IMetricsService& metricsService);
                        ~TwitterFeedTourModule();
                        
                        const std::map<std::string, TweetStateData>& GetTweetStateDataMap() const;
                    };
                }
            }
        }
    }
}