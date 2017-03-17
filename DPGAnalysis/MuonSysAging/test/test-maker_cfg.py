import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")
process.load("CondCore.CondDB.CondDB_cfi")
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.autoCond import autoCond
process.GlobalTag.globaltag = autoCond['run2_design']

process.CondDB.connect = 'sqlite_file:MuonSystemAging.db'

process.source = cms.Source("EmptyIOVSource",
    lastValue = cms.uint64(1),
    timetype = cms.string('runnumber'),
    firstValue = cms.uint64(1),
    interval = cms.uint64(1)
)

process.PoolDBOutputService = cms.Service("PoolDBOutputService",
    process.CondDB,
    timetype = cms.untracked.string('runnumber'),
    toPut = cms.VPSet(cms.PSet(
        record = cms.string('MuonSystemAgingRcd'),
        tag = cms.string('MuonSystemAging_test')
    ))
)

process.mytest = cms.EDAnalyzer("ChamberMasker",
           CSCineff = cms.double(0.15), 
#           maskedRPCIDs = cms.vint32([637570221]),
           maskedRPCIDs = cms.vstring(["637570221:0.0","637602989:0.5","637569561:0.7"]),
#           maskedRPCIDs = cms.vstring(["637555432:0.0","637554918:0.5"]),
           # Accept lists or regular expression as from:
           # http://www.cplusplus.com/reference/regex/ECMAScript/
           chamberRegEx = cms.vstring([
            # A chamber by chamber list in format CHAMBER:EFF
            # MB4 of top sectors
            "WH-2_ST4_SEC2:0.","WH-2_ST4_SEC3:0.","WH-2_ST4_SEC4:0.","WH-2_ST4_SEC5:0.","WH-2_ST4_SEC6:0.",
            "WH-1_ST4_SEC2:0.","WH-1_ST4_SEC3:0.","WH-1_ST4_SEC4:0.","WH-1_ST4_SEC5:0.","WH-1_ST4_SEC6:0.",
            "WH0_ST4_SEC2:0.","WH0_ST4_SEC3:0.","WH0_ST4_SEC4:0.","WH0_ST4_SEC5:0.","WH0_ST4_SEC6:0.",
            "WH1_ST4_SEC2:0.","WH1_ST4_SEC3:0.","WH1_ST4_SEC4:0.","WH1_ST4_SEC5:0.","WH1_ST4_SEC6:0.",
            "WH2_ST4_SEC2:0.","WH2_ST4_SEC3:0.","WH2_ST4_SEC4:0.","WH2_ST4_SEC5:0.","WH2_ST4_SEC6:0.",
            # MB1 of external wheels
            "WH-2_ST1_SEC1:0.","WH-2_ST1_SEC2:0.","WH-2_ST1_SEC3:0.","WH-2_ST1_SEC4:0.",
            "WH-2_ST1_SEC5:0.","WH-2_ST1_SEC6:0.","WH-2_ST1_SEC7:0.","WH-2_ST1_SEC8:0.",
            "WH-2_ST1_SEC9:0.","WH-2_ST1_SEC10:0.","WH-2_ST1_SEC11:0.","WH-2_ST1_SEC12:0.",
            "WH2_ST1_SEC1:0.","WH2_ST1_SEC2:0.","WH2_ST1_SEC3:0.","WH2_ST1_SEC4:0.",
            "WH2_ST1_SEC5:0.","WH2_ST1_SEC6:0.","WH2_ST1_SEC7:0.","WH2_ST1_SEC8:0.",
            "WH2_ST1_SEC9:0.","WH2_ST1_SEC10:0.","WH2_ST1_SEC11:0.","WH2_ST1_SEC12:0.",
            # 5 MB2s of external wheels
            "WH2_ST2_SEC3:0.","WH2_ST2_SEC6:0.","WH2_ST2_SEC9:0.",
            "WH-2_ST2_SEC2:0.","WH-2_ST2_SEC4:0.",
            # more sparse failures
            "WH-2_ST2_SEC8:0.","WH-1_ST1_SEC1:0.","WH-1_ST2_SEC1:0.","WH-1_ST1_SEC4:0.","WH-1_ST3_SEC7:0.",
            "WH0_ST2_SEC2:0.","WH0_ST3_SEC5:0.","WH0_ST4_SEC12:0.","WH1_ST1_SEC6:0.","WH1_ST1_SEC10:0.","WH1_ST3_SEC3:0."
            # Or a RegEx setting efficiency  for all chamber to 10%
            #"(WH-?\\\d_ST\\\d_SEC\\\\d+):0.1"
            ])
                                
)

process.p = cms.Path(process.mytest)

