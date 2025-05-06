#include "setupmanage.h"
#include "setupframe.h"
#include "setupplot.h"


SetupFrame *g_setupFrame = nullptr;

SetupManage::SetupManage()
{
    g_setupFrame = new SetupFrame();
    g_setupFrame->addPage("Plot",new setupPlot(g_setupFrame));

    g_setupFrame->addPage("Plot1",new setupPlot(g_setupFrame));
}

SetupManage::~SetupManage()
{
    delete g_setupFrame;
}

void SetupManage::show()
{
    g_setupFrame->show();
}
