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



def makeChPlots(tree,chan):
    evCounter=0
    h = ROOT.TH1F(chan,chan,50,1,-1)
    ROOT.SetOwnership(h,False)
    for event in tree:
        gr      = ROOT.TGraph()
        gr.SetTitle(chan+": event:"+str(evCounter))
        
        evCounter +=1
        print "Event: ",evCounter

        channel = getattr(event,chan)
        counter = 1
        for sample in channel:
            '''SetPoint(int entry, float x, floaty)'''
            gr.SetPoint(counter, (counter -1), sample)
            counter +=1


        minMax = getMinMax(gr)
        h.Fill(minMax[1] - minMax[0])

    print h.GetEntries()
    h.Draw()


#end of functions

##### Begining of main ####
'''''''Do the Analysis here'''''''
if(len(sys.argv)>1):
    f = ROOT.TFile(sys.argv[1])
    tree = f.Get("myTree")

    #makeChPlots(tree,"channel0") #TAC
    #makeChPlots(tree,"channel1") #Calo 1
    #makeChPlots(tree,"channel2") #Calo 2-7
    makeChPlots(tree,"channel3")  #PiStop
    #makeChPlots(tree,"channel4")
    #makeChPlots(tree,"channel5")
    #makeChPlots(tree,"channel6")

else:
    print "Expecting an input ROOT file"
