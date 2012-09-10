import ROOT
import sys

def getMinMax(plot):
    
    plot.GetXaxis().SetRangeUser(0,ROOT.TMath.MaxElement(plot.GetN(),plot.GetX()))
    minimum     = plot.GetMean(2)
    maximum     = ROOT.TMath.MaxElement(plot.GetN(),plot.GetY())

    '''plot.Draw("Alp")
    plot.GetYaxis().SetRangeUser(plot.GetMean(2) - plot.GetRMS(2),ROOT.TMath.MaxElement(plot.GetN(),plot.GetY())+ plot.GetRMS(2)*0.5)
    ROOT.gPad.WaitPrimitive()
    ROOT.gPad.Update()'''

    minMax  = (minimum,maximum)
    return minMax



def getChPlot(event,chan):
    gr      = ROOT.TGraph()
    evID    = event.EventNo
    gr.SetTitle(chan+": event:"+str(evID))
    
    print "Event: ",evID

    channel = getattr(event,chan)
    counter = 1
    for sample in channel:
        '''SetPoint(int entry, float x, floaty)'''
        gr.SetPoint(counter, (counter -1), sample)
        counter +=1

    return gr

def FillChannelSummary(tree, channel,hist):
    gr      = getChPlot(tree, channel)
    minmax  = getMinMax(gr)
    if(minmax[1] - minmax[0] > 10):
        hist.Fill( minmax[1] - minmax[0])
        
    gr.Draw("Alp")
    ROOT.gPad.Update()


#end of functions

##### Begining of main ####
'''''''Do the Analysis here'''''''
if(len(sys.argv)>1):
    f = ROOT.TFile(sys.argv[1])
    tree = f.Get("myTree")

    hlist = []
    hlist.append(ROOT.TH1F("Ch0","channel 0",500,1,-1))
    hlist.append(ROOT.TH1F("Ch1","channel 1",500,1,-1))
    hlist.append(ROOT.TH1F("Ch2","channel 2",500,1,-1))
    hlist.append(ROOT.TH1F("Ch3","channel 3",500,1,-1))
    hlist.append(ROOT.TH1F("Ch4","channel 4",500,1,-1))
    hlist.append(ROOT.TH1F("Ch5","channel 5",500,1,-1))
    hlist.append(ROOT.TH1F("Ch6","channel 6",500,1,-1))

    for event in tree:
        c1 = ROOT.TCanvas()
        #ROOT.SetOwnership(c1,False)
        for i in xrange(7):
            FillChannelSummary(tree,"channel"+str(i),hlist[i])


    c2 = ROOT.TCanvas()
    c2.Divide(2,4)
    for i in xrange(7):
        c2.cd(i+1)
        hlist[i].Draw()
