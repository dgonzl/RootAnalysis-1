#include <sstream>

#include "TestAnalyzer.h"
#include "TestHistograms.h"
#include "EventProxyTest.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
TestAnalyzer::TestAnalyzer(const std::string & aName):Analyzer(aName){ tmpName = "h1DXSignal";}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
TestAnalyzer::~TestAnalyzer(){ if(myHistos_) delete myHistos_; }
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
Analyzer* TestAnalyzer::clone() const{

  TestAnalyzer* clone = new TestAnalyzer(name());
  clone->setHistos(myHistos_);
  return clone;

};
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void TestAnalyzer::initialize(TFileDirectory& aDir,
				 pat::strbitset *aSelections){

  mySelections_ = aSelections;
  
  ///The histograms for this analyzer will be saved into "TestAnalyzer"
  ///directory of the ROOT file
  ///NOTE: due to a bug hists land in the Summary directory
  myHistos_ = new TestHistograms(&aDir, selectionFlavours_);
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void TestAnalyzer::finalize(){ 

  myHistos_->finalizeHistograms(0,1.0);
 
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
bool TestAnalyzer::analyze(const EventProxyBase& iEvent){

  const EventProxyTest & myEventProxy = static_cast<const EventProxyTest&>(iEvent);

  std::string sampleName = "Signal";
  
  tmpName = "h1DX"+sampleName;
  myHistos_->fill1DHistogram(tmpName,myEventProxy.x);

  tmpName = "h1DY"+sampleName;
  myHistos_->fill1DHistogram(tmpName,myEventProxy.y);

  return true;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

