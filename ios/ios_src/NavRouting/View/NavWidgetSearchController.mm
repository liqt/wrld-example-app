#import <Foundation/Foundation.h>

#include "NavWidgetSearchController.h"
#import <WrldSearchWidget/WrldSearchWidget.h>
#import "NavWidgetView.h"
#import "NavWidgetSearchView.h"
#include "WidgetSearchResultModel.h"

@interface NavWidgetSearchController()
@property BOOL isSearchingForStartPoint;
@property ResultSelectedEvent navSuggestionSelectedEvent;
@property QueryEvent navSearchRunEvent;
@end;

@implementation NavWidgetSearchController
{
    ExampleApp::NavRouting::View::NavWidgetView* m_pNavWidgetView;
    ExampleApp::NavRouting::View::NavWidgetSearchView* m_pSearchView;
}

- (instancetype) initWithSearchView: (ExampleApp::NavRouting::View::NavWidgetSearchView*) searchView navWidgetView : (ExampleApp::NavRouting::View::NavWidgetView*) pNavWidgetView
{
    if(self = [super init])
    {
        m_pNavWidgetView = pNavWidgetView;
        m_pSearchView = searchView;
        _isSearchingForStartPoint = NO;
        
        self.navSuggestionSelectedEvent = ^(id<WRLDSearchResultModel> selectedResultModel) {
            [self hideSearchView];
            WidgetSearchResultModel* selectedWidgetResult = (WidgetSearchResultModel*) selectedResultModel;
            if(selectedWidgetResult != nil)
            {
                [self navSuggestionSelected: (int)selectedWidgetResult.index];
            }
        };
        
        self.navSearchRunEvent = ^(WRLDSearchQuery *query) {
            [self hideSearchView];
        };
        
        m_pSearchView->AddSuggestionSelectedCallback(self.navSuggestionSelectedEvent);
        m_pSearchView->AddSearchStartedCallback(self.navSearchRunEvent);        
        m_pSearchView->AddCloseButtonTarget(self, @selector(closeSearchHandler:));
    }
    return self;
}

- (void) closeSearchHandler: (id) selector
{
    [self hideSearchView];
}

- (void) dealloc
{
    m_pSearchView->RemoveCloseButtonTarget(self, @selector(closeSearchHandler:));
    m_pSearchView->RemoveSearchStartedCallback(self.navSearchRunEvent);
    m_pSearchView->RemoveSuggestionSelectedCallback(self.navSuggestionSelectedEvent);
    [super dealloc];
}

- (void) navSuggestionSelected: (int) index
{
    if(self.isSearchingForStartPoint)
    {
        m_pNavWidgetView->SetStartPointFromSuggestionIndex(index);
    }
    else
    {
        m_pNavWidgetView->SetEndPointFromSuggestionIndex(index);
    }
}

- (void) eventReceived: (WRLDNavEvent) key
{
    switch(key){
        case WRLDNavEventSelectStartLocationClicked:
            _isSearchingForStartPoint = YES;
            [self showSearchView];
            break;
        case WRLDNavEventSelectEndLocationClicked:
            _isSearchingForStartPoint = NO;
            [self showSearchView];
            break;
        default:
            break;
    }
}

- (void) showSearchView
{
    m_pNavWidgetView->Hide();
    m_pSearchView->Show();
}

- (void) hideSearchView
{
    m_pNavWidgetView->Show();
    m_pSearchView->Hide();
}
@end
