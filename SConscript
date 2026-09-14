import os
from building import *

objs = []
cwd  = GetCurrentDir()

if GetDepend(['ARCH_ARM_CORTEX_M']):
    objs = objs + SConscript('CMSIS/SConscript')

if GetDepend(['SOC_SERIES_MA35D1']):
    objs = objs + SConscript('MA35D1/SConscript')

if GetDepend(['SOC_SERIES_M460']):
    objs = objs + SConscript('M460/SConscript')

if GetDepend(['SOC_SERIES_M480']):
    objs = objs + SConscript('M480/SConscript')

if GetDepend(['SOC_SERIES_M031']):
    objs = objs + SConscript('M031/SConscript')

if GetDepend(['SOC_SERIES_M2354']):
    objs = objs + SConscript('M2354/SConscript')

if GetDepend(['SOC_SERIES_M3331']):
    objs = objs + SConscript('M3331/SConscript')

if GetDepend(['SOC_SERIES_M2L31']):
    objs = objs + SConscript('M2L31/SConscript')

if GetDepend(['SOC_SERIES_M3351']):
    objs = objs + SConscript('M3351/SConscript')

if GetDepend(['SOC_SERIES_M5531']):
    objs = objs + SConscript('M5531/SConscript')

if GetDepend(['SOC_SERIES_N9H30']):
    objs = objs + SConscript('N9H30/SConscript')

if GetDepend(['SOC_SERIES_NUC980']):
    objs = objs + SConscript('NUC980/SConscript')

Return('objs')
