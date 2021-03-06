#include "clTabTogglerHelper.h"
#include "event_notifier.h"
#include "codelite_events.h"
#include "globals.h"
#include "imanager.h"
#include "Notebook.h"

clTabTogglerHelper::clTabTogglerHelper(const wxString& outputTabName,
                                       wxWindow* outputTab,
                                       const wxString& workspaceTabName,
                                       wxWindow* workspaceTab)
    : m_outputTabName(outputTabName)
    , m_outputTab(outputTab)
    , m_workspaceTabName(workspaceTabName)
    , m_workspaceTab(workspaceTab)
{
    if(m_workspaceTab && !m_workspaceTabName.IsEmpty()) {
        EventNotifier::Get()->Bind(wxEVT_SHOW_WORKSPACE_TAB, &clTabTogglerHelper::OnToggleWorkspaceTab, this);
        clGetManager()->AddWorkspaceTab(m_workspaceTabName);
    }
    if(m_outputTab && !m_outputTabName.IsEmpty()) {
        EventNotifier::Get()->Bind(wxEVT_SHOW_OUTPUT_TAB, &clTabTogglerHelper::OnToggleOutputTab, this);
        clGetManager()->AddOutputTab(m_outputTabName);
    }
}

clTabTogglerHelper::~clTabTogglerHelper()
{
    if(m_workspaceTab && !m_workspaceTabName.IsEmpty()) {
        EventNotifier::Get()->Unbind(wxEVT_SHOW_WORKSPACE_TAB, &clTabTogglerHelper::OnToggleWorkspaceTab, this);
    }
    if(m_outputTab && !m_outputTabName.IsEmpty()) {
        EventNotifier::Get()->Unbind(wxEVT_SHOW_OUTPUT_TAB, &clTabTogglerHelper::OnToggleOutputTab, this);
    }
}

void clTabTogglerHelper::OnToggleOutputTab(clCommandEvent& event)
{
    if(event.GetString() != m_outputTabName) {
        event.Skip();
        return;
    }

    if(event.IsSelected()) {
        // show it
        clGetManager()->GetOutputPaneNotebook()->InsertPage(0, m_outputTab, m_outputTabName, true, m_outputTabBmp);

    } else {
        int where = clGetManager()->GetOutputPaneNotebook()->GetPageIndex(m_outputTabName);
        if(where != wxNOT_FOUND) {
            clGetManager()->GetOutputPaneNotebook()->RemovePage(where);
        }
    }
}

void clTabTogglerHelper::OnToggleWorkspaceTab(clCommandEvent& event)
{
    if(event.GetString() != m_workspaceTabName) {
        event.Skip();
        return;
    }

    if(event.IsSelected()) {
        // show it
        clGetManager()->GetWorkspacePaneNotebook()->InsertPage(
            0, m_workspaceTab, m_workspaceTabName, true, m_workspaceTabBmp);
    } else {
        int where = clGetManager()->GetWorkspacePaneNotebook()->GetPageIndex(m_workspaceTabName);
        if(where != wxNOT_FOUND) {
            clGetManager()->GetWorkspacePaneNotebook()->RemovePage(where);
        }
    }
}
