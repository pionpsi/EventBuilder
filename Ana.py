import ROOT

def getChPlots(tree,chan):
    grList  = []

    evCounter=0
    for event in tree:
        gr      = ROOT.TGraph()
        gr.SetTitle(chan+": event:"+str(evCounter))

        channel = getattr(event,chan)
        
        counter = 1
        for sample in channel:
            '''SetPoint(int entry, float x, floaty)'''
            gr.SetPoint(counter, (counter -1), sample)
            counter +=1

        grList.append(gr)

    return grList

#end of function
'''''''Do the Analysis here'''''''
f = ROOT.TFile("output.root")
tree = f.Get("rawStream_0451")

ch0Plots    = getChPlots(tree,"channel0")
ch1Plots    = getChPlots(tree,"channel1")
ch2Plots    = getChPlots(tree,"channel2")
ch3Plots    = getChPlots(tree,"channel3")
ch4Plots    = getChPlots(tree,"channel4")
ch5Plots    = getChPlots(tree,"channel5")
ch6Plots    = getChPlots(tree,"channel6")

for plots in ch1Plots:
    plots.Draw("Al")

