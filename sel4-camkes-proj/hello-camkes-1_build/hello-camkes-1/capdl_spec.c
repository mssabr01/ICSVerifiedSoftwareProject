/* Generated file. Your changes will be overwritten. */

#include <capdl.h>

#ifndef INVALID_SLOT
#define INVALID_SLOT (-1)
#endif

#define MAX_OBJECTS 1301

CDL_Model capdl_spec = {
#if !defined(CONFIG_ARCH_X86_64)
#    error "invalid target architecture; expecting X86_64"
#endif
.num = 1301,
.irqs = {
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
},
.objects = (CDL_Object[]) {
[0] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "crypto_frame__camkes_ipc_buffer_crypto_0_control",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "crypto_frame__camkes_ipc_buffer_crypto_0_fault_handler_0000",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[2] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "crypto_frame__camkes_ipc_buffer_crypto_crypto_iface_0000",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[3] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "crypto_group_bin_pd",
#endif
.type = CDL_PML4,
.slots.num = 1,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_PDPTCap, .obj_id = 1205 /* pdpt_crypto_group_bin_0000 */, .is_orig = true}},

},
},
[4] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0000",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[5] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0001",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[6] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0002",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[7] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0003",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[8] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0004",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[9] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0005",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[10] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0006",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[11] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0007",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[12] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0008",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[13] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0009",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[14] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0010",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[15] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0011",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[16] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0012",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[17] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0013",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[18] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0014",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[19] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0015",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[20] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0016",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[21] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0017",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[22] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0018",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[23] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0019",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[24] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0020",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[25] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0021",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[26] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0022",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[27] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0023",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[28] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0024",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[29] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0025",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[30] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0026",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[31] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0027",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[32] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0028",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[33] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0029",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[34] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0030",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[35] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0031",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[36] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0032",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[37] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0035",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[38] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0037",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[39] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0038",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[40] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0039",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[41] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0041",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[42] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0042",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[43] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0043",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[44] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0044",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[45] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0045",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[46] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0046",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[47] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0047",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[48] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0048",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[49] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0049",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[50] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0051",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[51] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0052",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[52] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0053",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[53] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0054",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[54] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0055",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[55] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0056",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[56] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0057",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[57] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0058",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[58] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0059",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[59] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0060",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[60] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0061",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[61] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0062",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[62] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0063",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[63] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0065",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[64] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0067",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[65] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0068",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[66] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0070",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[67] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0071",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[68] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0072",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[69] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0073",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[70] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0074",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[71] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0075",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[72] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0076",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[73] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0077",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[74] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0078",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[75] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0080",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[76] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0081",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[77] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0083",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[78] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0084",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[79] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0085",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[80] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0086",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[81] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0087",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[82] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0088",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[83] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0089",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[84] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0090",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[85] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0091",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[86] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0092",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[87] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0093",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[88] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0094",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[89] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0095",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[90] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0096",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[91] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0097",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[92] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0098",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[93] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0099",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[94] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0100",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[95] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0101",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[96] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0102",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[97] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0104",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[98] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0105",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[99] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0106",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[100] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0107",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[101] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0108",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[102] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0109",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[103] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0111",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[104] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0112",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[105] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0114",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[106] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0115",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[107] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0116",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[108] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0117",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[109] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0118",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[110] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0119",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[111] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0120",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[112] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0121",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[113] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0122",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[114] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0123",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[115] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0124",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[116] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0125",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[117] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0126",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[118] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0127",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[119] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0128",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[120] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0129",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[121] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0130",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[122] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0131",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[123] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0132",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[124] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0133",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[125] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0134",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[126] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0136",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[127] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0137",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[128] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0138",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[129] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0139",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[130] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0140",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[131] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0141",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[132] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0142",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[133] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0143",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[134] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0144",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[135] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0145",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[136] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0146",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[137] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0147",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[138] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0148",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[139] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0149",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[140] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0151",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[141] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0152",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[142] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0153",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[143] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0154",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[144] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0155",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[145] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0156",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[146] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0158",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[147] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0159",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[148] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0160",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[149] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0161",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[150] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0162",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[151] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0163",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[152] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0164",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[153] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0165",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[154] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0166",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[155] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0167",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[156] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0168",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[157] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0169",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[158] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0170",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[159] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0171",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[160] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0172",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[161] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0174",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[162] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0175",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[163] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0177",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[164] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0178",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[165] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0179",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[166] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0180",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[167] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0181",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[168] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0182",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[169] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0184",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[170] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0185",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[171] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0186",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[172] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0187",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[173] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0188",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[174] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0189",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[175] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0190",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[176] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0191",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[177] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0192",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[178] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0193",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[179] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0194",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[180] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0195",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[181] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0196",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[182] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0197",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[183] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0198",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[184] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0199",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[185] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0200",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[186] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0201",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[187] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0202",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[188] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0203",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[189] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0204",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[190] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0205",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[191] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0206",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[192] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0207",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[193] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0208",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[194] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0209",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[195] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0210",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[196] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0211",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[197] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0212",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[198] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0213",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[199] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0214",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[200] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0215",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[201] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0216",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[202] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0217",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[203] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0218",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[204] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0219",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[205] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0221",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[206] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0222",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[207] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0223",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[208] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0224",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[209] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0225",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[210] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0226",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[211] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0227",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[212] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0229",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[213] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0230",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[214] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0231",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[215] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0232",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[216] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0233",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[217] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0234",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[218] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0235",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[219] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0236",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[220] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0237",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[221] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0238",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[222] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0239",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[223] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0240",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[224] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0241",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[225] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0242",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[226] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0243",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[227] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0244",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[228] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0245",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[229] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0246",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[230] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0247",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[231] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0249",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[232] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0250",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[233] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0251",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[234] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0252",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[235] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0253",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[236] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0254",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[237] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0256",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[238] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0257",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[239] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0258",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[240] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0259",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[241] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0260",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[242] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0261",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[243] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0262",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[244] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0263",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[245] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0264",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[246] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0265",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[247] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0266",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[248] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0267",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[249] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0268",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[250] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0269",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[251] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0270",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[252] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0271",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[253] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0272",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[254] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0273",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[255] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0274",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[256] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0275",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[257] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0276",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[258] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0277",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[259] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0278",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[260] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0279",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[261] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0280",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[262] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0281",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[263] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0282",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[264] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0283",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[265] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0284",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[266] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0285",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[267] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0286",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[268] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0287",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[269] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0289",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[270] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0290",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[271] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0291",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[272] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0292",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[273] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0293",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[274] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0294",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[275] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0295",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[276] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0296",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[277] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0297",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[278] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0298",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[279] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0299",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[280] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0300",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[281] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0301",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[282] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0302",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[283] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0304",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[284] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0305",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[285] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0306",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[286] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0307",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[287] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0308",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[288] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0309",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[289] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0310",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[290] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0311",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[291] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0312",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[292] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0313",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[293] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0314",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[294] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0315",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[295] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0317",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[296] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0319",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[297] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0320",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[298] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0321",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[299] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0322",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[300] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0323",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[301] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_crypto_group_bin_0324",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[302] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0000",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[303] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0001",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[304] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0002",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[305] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0003",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[306] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0004",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[307] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0005",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[308] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0006",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[309] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0007",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[310] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0008",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[311] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0010",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[312] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0011",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[313] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0012",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[314] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0013",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[315] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0014",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[316] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0015",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[317] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0016",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[318] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0017",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[319] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0018",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[320] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0019",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[321] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0020",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[322] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0021",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[323] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0022",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[324] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0023",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[325] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0024",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[326] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0025",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[327] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0026",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[328] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0027",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[329] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0028",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[330] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0029",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[331] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0030",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[332] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0031",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[333] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0032",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[334] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0035",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[335] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0037",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[336] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0038",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[337] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0039",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[338] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0041",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[339] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0042",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[340] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0043",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[341] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0044",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[342] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0045",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[343] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0046",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[344] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0047",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[345] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0048",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[346] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0049",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[347] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0051",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[348] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0052",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[349] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0053",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[350] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0054",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[351] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0055",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[352] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0056",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[353] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0057",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[354] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0058",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[355] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0059",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[356] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0060",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[357] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0061",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[358] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0062",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[359] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0063",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[360] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0065",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[361] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0067",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[362] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0068",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[363] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0070",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[364] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0071",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[365] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0072",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[366] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0073",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[367] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0074",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[368] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0075",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[369] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0076",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[370] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0077",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[371] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0078",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[372] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0080",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[373] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0081",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[374] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0083",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[375] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0084",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[376] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0085",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[377] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0086",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[378] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0087",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[379] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0088",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[380] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0089",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[381] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0090",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[382] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0091",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[383] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0092",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[384] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0093",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[385] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0094",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[386] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0095",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[387] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0096",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[388] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0097",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[389] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0098",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[390] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0099",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[391] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0100",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[392] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0101",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[393] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0102",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[394] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0104",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[395] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0105",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[396] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0106",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[397] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0107",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[398] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0108",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[399] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0109",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[400] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0111",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[401] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0112",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[402] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0114",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[403] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0115",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[404] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0116",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[405] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0117",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[406] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0118",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[407] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0119",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[408] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0120",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[409] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0121",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[410] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0122",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[411] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0123",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[412] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0124",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[413] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0125",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[414] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0126",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[415] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0127",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[416] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0128",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[417] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0129",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[418] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0130",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[419] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0131",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[420] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0132",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[421] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0133",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[422] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0134",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[423] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0136",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[424] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0137",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[425] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0138",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[426] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0139",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[427] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0140",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[428] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0141",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[429] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0142",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[430] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0143",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[431] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0144",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[432] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0145",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[433] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0146",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[434] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0147",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[435] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0148",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[436] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0149",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[437] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0150",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[438] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0151",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[439] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0152",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[440] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0153",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[441] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0154",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[442] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0155",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[443] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0157",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[444] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0158",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[445] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0159",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[446] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0160",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[447] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0161",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[448] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0162",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[449] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0163",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[450] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0164",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[451] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0165",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[452] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0166",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[453] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0167",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[454] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0168",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[455] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0169",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[456] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0170",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[457] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0171",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[458] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0173",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[459] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0174",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[460] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0176",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[461] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0177",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[462] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0178",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[463] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0179",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[464] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0180",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[465] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0181",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[466] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0183",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[467] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0184",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[468] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0185",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[469] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0186",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[470] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0187",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[471] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0188",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[472] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0189",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[473] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0190",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[474] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0191",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[475] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0192",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[476] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0193",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[477] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0194",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[478] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0195",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[479] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0196",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[480] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0197",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[481] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0198",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[482] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0199",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[483] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0200",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[484] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0201",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[485] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0202",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[486] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0203",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[487] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0204",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[488] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0205",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[489] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0206",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[490] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0207",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[491] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0208",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[492] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0209",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[493] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0210",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[494] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0211",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[495] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0212",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[496] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0213",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[497] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0214",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[498] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0215",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[499] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0216",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[500] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0217",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[501] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0218",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[502] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0220",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[503] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0221",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[504] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0222",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[505] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0223",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[506] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0224",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[507] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0225",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[508] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0226",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[509] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0228",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[510] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0229",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[511] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0230",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[512] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0231",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[513] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0232",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[514] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0233",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[515] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0234",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[516] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0235",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[517] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0236",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[518] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0237",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[519] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0238",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[520] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0239",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[521] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0240",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[522] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0241",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[523] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0242",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[524] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0243",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[525] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0244",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[526] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0245",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[527] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0246",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[528] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0248",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[529] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0249",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[530] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0250",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[531] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0251",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[532] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0252",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[533] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0253",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[534] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0255",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[535] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0256",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[536] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0257",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[537] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0258",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[538] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0259",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[539] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0260",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[540] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0261",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[541] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0262",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[542] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0263",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[543] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0264",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[544] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0265",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[545] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0266",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[546] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0267",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[547] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0268",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[548] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0269",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[549] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0270",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[550] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0271",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[551] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0272",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[552] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0273",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[553] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0274",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[554] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0275",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[555] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0276",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[556] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0277",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[557] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0278",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[558] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0279",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[559] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0280",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[560] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0281",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[561] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0282",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[562] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0283",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[563] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0284",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[564] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0285",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[565] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0286",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[566] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0288",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[567] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0289",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[568] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0290",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[569] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0291",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[570] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0292",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[571] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0293",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[572] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0294",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[573] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0295",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[574] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0296",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[575] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0297",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[576] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0298",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[577] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0299",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[578] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0300",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[579] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0301",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[580] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0303",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[581] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0304",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[582] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0305",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[583] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0306",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[584] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0307",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[585] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0308",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[586] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0309",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[587] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0310",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[588] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0311",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[589] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0312",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[590] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0313",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[591] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0314",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[592] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0316",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[593] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0318",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[594] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0319",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[595] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0320",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[596] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0321",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[597] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0322",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[598] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modchk_group_bin_0323",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[599] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0000",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[600] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0001",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[601] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0002",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[602] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0003",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[603] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0004",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[604] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0005",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[605] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0006",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[606] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0007",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[607] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0008",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[608] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0010",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[609] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0011",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[610] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0012",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[611] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0013",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[612] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0014",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[613] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0015",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[614] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0016",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[615] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0017",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[616] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0018",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[617] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0019",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[618] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0020",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[619] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0021",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[620] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0022",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[621] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0023",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[622] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0024",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[623] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0025",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[624] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0026",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[625] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0027",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[626] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0028",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[627] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0029",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[628] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0030",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[629] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0031",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[630] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0032",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[631] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0035",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[632] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0037",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[633] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0038",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[634] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0039",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[635] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0041",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[636] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0042",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[637] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0043",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[638] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0044",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[639] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0045",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[640] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0046",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[641] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0047",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[642] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0048",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[643] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0049",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[644] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0051",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[645] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0052",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[646] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0053",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[647] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0054",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[648] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0055",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[649] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0056",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[650] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0057",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[651] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0058",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[652] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0059",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[653] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0060",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[654] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0061",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[655] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0062",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[656] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0063",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[657] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0065",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[658] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0067",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[659] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0068",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[660] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0070",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[661] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0071",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[662] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0072",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[663] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0073",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[664] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0074",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[665] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0075",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[666] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0076",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[667] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0077",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[668] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0078",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[669] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0080",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[670] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0081",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[671] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0083",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[672] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0084",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[673] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0085",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[674] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0086",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[675] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0087",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[676] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0088",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[677] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0089",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[678] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0090",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[679] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0091",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[680] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0092",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[681] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0093",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[682] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0094",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[683] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0095",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[684] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0096",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[685] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0097",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[686] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0098",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[687] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0099",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[688] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0100",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[689] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0101",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[690] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0102",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[691] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0104",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[692] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0105",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[693] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0106",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[694] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0107",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[695] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0108",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[696] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0109",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[697] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0111",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[698] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0112",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[699] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0114",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[700] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0115",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[701] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0116",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[702] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0117",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[703] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0118",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[704] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0119",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[705] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0120",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[706] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0121",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[707] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0122",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[708] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0123",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[709] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0124",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[710] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0125",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[711] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0126",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[712] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0127",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[713] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0128",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[714] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0129",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[715] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0130",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[716] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0131",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[717] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0132",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[718] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0133",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[719] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0134",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[720] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0136",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[721] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0137",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[722] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0138",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[723] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0139",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[724] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0140",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[725] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0141",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[726] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0142",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[727] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0143",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[728] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0144",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[729] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0145",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[730] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0146",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[731] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0147",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[732] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0148",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[733] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0149",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[734] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0150",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[735] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0151",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[736] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0152",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[737] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0153",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[738] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0154",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[739] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0155",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[740] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0157",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[741] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0158",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[742] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0159",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[743] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0160",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[744] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0161",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[745] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0162",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[746] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0163",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[747] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0164",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[748] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0165",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[749] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0166",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[750] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0167",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[751] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0168",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[752] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0169",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[753] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0170",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[754] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0171",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[755] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0172",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[756] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0173",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[757] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0175",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[758] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0176",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[759] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0177",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[760] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0178",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[761] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0179",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[762] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0180",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[763] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0182",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[764] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0183",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[765] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0184",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[766] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0185",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[767] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0186",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[768] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0187",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[769] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0188",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[770] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0189",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[771] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0190",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[772] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0191",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[773] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0192",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[774] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0193",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[775] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0194",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[776] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0195",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[777] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0196",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[778] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0197",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[779] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0198",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[780] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0199",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[781] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0200",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[782] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0201",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[783] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0202",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[784] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0203",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[785] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0204",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[786] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0205",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[787] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0206",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[788] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0207",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[789] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0208",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[790] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0209",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[791] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0210",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[792] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0211",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[793] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0212",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[794] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0213",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[795] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0214",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[796] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0215",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[797] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0216",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[798] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0217",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[799] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0219",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[800] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0220",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[801] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0221",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[802] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0222",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[803] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0223",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[804] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0224",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[805] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0225",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[806] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0227",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[807] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0228",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[808] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0229",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[809] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0230",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[810] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0231",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[811] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0232",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[812] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0233",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[813] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0234",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[814] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0235",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[815] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0236",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[816] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0237",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[817] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0238",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[818] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0239",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[819] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0240",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[820] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0241",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[821] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0242",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[822] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0243",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[823] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0244",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[824] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0245",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[825] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0247",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[826] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0248",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[827] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0249",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[828] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0250",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[829] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0251",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[830] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0252",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[831] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0254",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[832] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0255",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[833] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0256",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[834] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0257",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[835] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0259",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[836] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0260",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[837] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0261",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[838] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0262",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[839] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0263",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[840] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0264",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[841] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0265",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[842] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0266",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[843] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0267",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[844] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0268",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[845] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0269",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[846] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0270",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[847] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0271",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[848] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0272",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[849] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0273",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[850] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0274",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[851] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0275",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[852] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0276",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[853] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0277",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[854] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0278",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[855] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0279",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[856] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0280",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[857] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0281",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[858] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0282",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[859] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0283",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[860] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0284",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[861] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0285",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[862] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0287",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[863] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0288",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[864] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0289",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[865] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0290",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[866] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0291",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[867] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0292",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[868] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0293",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[869] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0294",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[870] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0295",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[871] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0296",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[872] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0297",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[873] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0298",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[874] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0299",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[875] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0300",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[876] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0302",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[877] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0303",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[878] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0304",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[879] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0305",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[880] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0306",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[881] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0307",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[882] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0308",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[883] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0309",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[884] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0310",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[885] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0311",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[886] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0312",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[887] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0313",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[888] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0315",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[889] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0317",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[890] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0318",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[891] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0319",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[892] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0320",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[893] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0321",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[894] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_modtx_group_bin_0322",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[895] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0000",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[896] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0001",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[897] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0002",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[898] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0003",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[899] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0004",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[900] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0005",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[901] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0006",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[902] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0007",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[903] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0008",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[904] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0009",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[905] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0010",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[906] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0011",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[907] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0012",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[908] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0013",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[909] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0014",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[910] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0015",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[911] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0016",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[912] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0017",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[913] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0018",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[914] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0019",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[915] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0020",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[916] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0021",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[917] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0022",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[918] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0023",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[919] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0024",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[920] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0025",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[921] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0026",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[922] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0027",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[923] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0028",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[924] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0029",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[925] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0030",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[926] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0031",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[927] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0032",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[928] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0035",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[929] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0037",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[930] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0038",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[931] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0039",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[932] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0041",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[933] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0042",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[934] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0043",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[935] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0044",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[936] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0045",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[937] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0046",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[938] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0047",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[939] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0048",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[940] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0049",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[941] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0051",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[942] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0052",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[943] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0053",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[944] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0054",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[945] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0055",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[946] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0056",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[947] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0057",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[948] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0058",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[949] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0059",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[950] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0060",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[951] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0061",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[952] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0062",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[953] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0063",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[954] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0065",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[955] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0067",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[956] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0068",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[957] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0070",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[958] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0071",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[959] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0072",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[960] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0073",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[961] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0074",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[962] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0075",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[963] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0076",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[964] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0077",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[965] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0078",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[966] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0080",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[967] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0081",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[968] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0083",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[969] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0084",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[970] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0085",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[971] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0086",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[972] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0087",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[973] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0088",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[974] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0089",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[975] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0090",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[976] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0091",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[977] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0092",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[978] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0093",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[979] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0094",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[980] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0095",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[981] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0096",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[982] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0097",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[983] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0098",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[984] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0099",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[985] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0100",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[986] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0101",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[987] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0102",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[988] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0104",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[989] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0105",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[990] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0106",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[991] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0107",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[992] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0108",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[993] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0109",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[994] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0111",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[995] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0112",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[996] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0114",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[997] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0115",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[998] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0116",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[999] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0117",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1000] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0118",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1001] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0119",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1002] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0120",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1003] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0121",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1004] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0122",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1005] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0123",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1006] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0124",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1007] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0125",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1008] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0126",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1009] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0127",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1010] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0128",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1011] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0129",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1012] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0130",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1013] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0131",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1014] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0132",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1015] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0133",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1016] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0134",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1017] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0136",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1018] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0137",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1019] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0138",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1020] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0139",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1021] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0140",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1022] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0141",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1023] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0142",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1024] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0143",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1025] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0144",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1026] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0145",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1027] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0146",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1028] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0147",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1029] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0148",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1030] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0149",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1031] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0151",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1032] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0152",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1033] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0153",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1034] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0154",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1035] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0155",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1036] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0156",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1037] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0158",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1038] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0159",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1039] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0160",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1040] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0161",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1041] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0162",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1042] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0163",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1043] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0164",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1044] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0165",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1045] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0166",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1046] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0167",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1047] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0168",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1048] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0169",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1049] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0170",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1050] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0171",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1051] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0172",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1052] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0174",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1053] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0175",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1054] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0177",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1055] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0178",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1056] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0179",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1057] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0180",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1058] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0181",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1059] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0182",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1060] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0184",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1061] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0185",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1062] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0186",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1063] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0187",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1064] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0188",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1065] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0189",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1066] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0190",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1067] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0191",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1068] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0192",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1069] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0193",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1070] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0194",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1071] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0195",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1072] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0196",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1073] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0197",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1074] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0198",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1075] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0199",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1076] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0200",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1077] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0201",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1078] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0202",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1079] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0203",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1080] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0204",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1081] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0205",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1082] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0206",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1083] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0207",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1084] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0208",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1085] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0209",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1086] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0210",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1087] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0211",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1088] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0212",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1089] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0213",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1090] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0214",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1091] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0215",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1092] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0216",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1093] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0217",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1094] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0218",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1095] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0219",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1096] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0221",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1097] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0222",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1098] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0223",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1099] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0224",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1100] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0225",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1101] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0226",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1102] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0227",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1103] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0229",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1104] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0230",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1105] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0231",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1106] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0232",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1107] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0233",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1108] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0234",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1109] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0235",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1110] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0236",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1111] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0237",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1112] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0238",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1113] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0239",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1114] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0240",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1115] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0241",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1116] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0242",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1117] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0243",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1118] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0244",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1119] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0245",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1120] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0246",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1121] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0247",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1122] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0249",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1123] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0250",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1124] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0251",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1125] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0252",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1126] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0253",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1127] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0254",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1128] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0256",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1129] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0257",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1130] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0258",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1131] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0259",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1132] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0260",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1133] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0261",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1134] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0262",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1135] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0263",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1136] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0264",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1137] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0265",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1138] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0266",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1139] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0267",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1140] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0268",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1141] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0269",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1142] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0270",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1143] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0271",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1144] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0272",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1145] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0273",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1146] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0274",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1147] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0275",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1148] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0276",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1149] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0277",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1150] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0278",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1151] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0279",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1152] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0280",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1153] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0281",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1154] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0282",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1155] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0283",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1156] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0284",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1157] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0285",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1158] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0286",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1159] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0287",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1160] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0289",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1161] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0290",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1162] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0291",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1163] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0292",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1164] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0293",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1165] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0294",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1166] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0295",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1167] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0296",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1168] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0297",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1169] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0298",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1170] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0299",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1171] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0300",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1172] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0301",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1173] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0302",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1174] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0304",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1175] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0305",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1176] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0306",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1177] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0307",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1178] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0308",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1179] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0309",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1180] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0310",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1181] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0311",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1182] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0312",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1183] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0313",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1184] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0314",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1185] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0315",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1186] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0317",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1187] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0319",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1188] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0320",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1189] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0321",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1190] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0322",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1191] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0323",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1192] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "frame_signtx_group_bin_0324",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1193] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modchk_frame__camkes_ipc_buffer_modchk_0_control",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1194] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modchk_frame__camkes_ipc_buffer_modchk_0_fault_handler_0000",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1195] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modchk_frame__camkes_ipc_buffer_modchk_modchk_iface_0000",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1196] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modchk_group_bin_pd",
#endif
.type = CDL_PML4,
.slots.num = 1,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_PDPTCap, .obj_id = 1206 /* pdpt_modchk_group_bin_0000 */, .is_orig = true}},

},
},
[1197] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modtx_frame__camkes_ipc_buffer_modtx_0_control",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1198] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modtx_frame__camkes_ipc_buffer_modtx_0_fault_handler_0000",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1199] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modtx_frame__camkes_ipc_buffer_modtx_modtx_iface_0000",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1200] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modtx_group_bin_pd",
#endif
.type = CDL_PML4,
.slots.num = 1,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_PDPTCap, .obj_id = 1207 /* pdpt_modtx_group_bin_0000 */, .is_orig = true}},

},
},
[1201] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "pd_crypto_group_bin_0001",
#endif
.type = CDL_PD,
.slots.num = 1,
.slots.slot = (CDL_CapSlot[]) {
{2, {.type = CDL_PTCap, .obj_id = 1209 /* pt_crypto_group_bin_0002 */, .is_orig = true}},

},
},
[1202] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "pd_modchk_group_bin_0001",
#endif
.type = CDL_PD,
.slots.num = 1,
.slots.slot = (CDL_CapSlot[]) {
{2, {.type = CDL_PTCap, .obj_id = 1210 /* pt_modchk_group_bin_0002 */, .is_orig = true}},

},
},
[1203] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "pd_modtx_group_bin_0001",
#endif
.type = CDL_PD,
.slots.num = 1,
.slots.slot = (CDL_CapSlot[]) {
{2, {.type = CDL_PTCap, .obj_id = 1211 /* pt_modtx_group_bin_0002 */, .is_orig = true}},

},
},
[1204] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "pd_signtx_group_bin_0001",
#endif
.type = CDL_PD,
.slots.num = 1,
.slots.slot = (CDL_CapSlot[]) {
{2, {.type = CDL_PTCap, .obj_id = 1212 /* pt_signtx_group_bin_0002 */, .is_orig = true}},

},
},
[1205] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "pdpt_crypto_group_bin_0000",
#endif
.type = CDL_PDPT,
.slots.num = 1,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_PDCap, .obj_id = 1201 /* pd_crypto_group_bin_0001 */, .is_orig = true}},

},
},
[1206] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "pdpt_modchk_group_bin_0000",
#endif
.type = CDL_PDPT,
.slots.num = 1,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_PDCap, .obj_id = 1202 /* pd_modchk_group_bin_0001 */, .is_orig = true}},

},
},
[1207] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "pdpt_modtx_group_bin_0000",
#endif
.type = CDL_PDPT,
.slots.num = 1,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_PDCap, .obj_id = 1203 /* pd_modtx_group_bin_0001 */, .is_orig = true}},

},
},
[1208] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "pdpt_signtx_group_bin_0000",
#endif
.type = CDL_PDPT,
.slots.num = 1,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_PDCap, .obj_id = 1204 /* pd_signtx_group_bin_0001 */, .is_orig = true}},

},
},
[1209] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "pt_crypto_group_bin_0002",
#endif
.type = CDL_PT,
.slots.num = 313,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_FrameCap, .obj_id = 4 /* frame_crypto_group_bin_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{1, {.type = CDL_FrameCap, .obj_id = 5 /* frame_crypto_group_bin_0001 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{2, {.type = CDL_FrameCap, .obj_id = 175 /* frame_crypto_group_bin_0190 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{3, {.type = CDL_FrameCap, .obj_id = 252 /* frame_crypto_group_bin_0271 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{4, {.type = CDL_FrameCap, .obj_id = 32 /* frame_crypto_group_bin_0028 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{5, {.type = CDL_FrameCap, .obj_id = 109 /* frame_crypto_group_bin_0118 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{6, {.type = CDL_FrameCap, .obj_id = 184 /* frame_crypto_group_bin_0199 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{7, {.type = CDL_FrameCap, .obj_id = 262 /* frame_crypto_group_bin_0281 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{8, {.type = CDL_FrameCap, .obj_id = 41 /* frame_crypto_group_bin_0041 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{9, {.type = CDL_FrameCap, .obj_id = 117 /* frame_crypto_group_bin_0126 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{10, {.type = CDL_FrameCap, .obj_id = 194 /* frame_crypto_group_bin_0209 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{11, {.type = CDL_FrameCap, .obj_id = 272 /* frame_crypto_group_bin_0292 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{12, {.type = CDL_FrameCap, .obj_id = 49 /* frame_crypto_group_bin_0049 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{13, {.type = CDL_FrameCap, .obj_id = 127 /* frame_crypto_group_bin_0137 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{14, {.type = CDL_FrameCap, .obj_id = 203 /* frame_crypto_group_bin_0218 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{15, {.type = CDL_FrameCap, .obj_id = 282 /* frame_crypto_group_bin_0302 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{16, {.type = CDL_FrameCap, .obj_id = 59 /* frame_crypto_group_bin_0060 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{17, {.type = CDL_FrameCap, .obj_id = 136 /* frame_crypto_group_bin_0146 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{18, {.type = CDL_FrameCap, .obj_id = 211 /* frame_crypto_group_bin_0227 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{19, {.type = CDL_FrameCap, .obj_id = 291 /* frame_crypto_group_bin_0312 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{20, {.type = CDL_FrameCap, .obj_id = 67 /* frame_crypto_group_bin_0071 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{21, {.type = CDL_FrameCap, .obj_id = 145 /* frame_crypto_group_bin_0156 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{22, {.type = CDL_FrameCap, .obj_id = 222 /* frame_crypto_group_bin_0239 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{23, {.type = CDL_FrameCap, .obj_id = 299 /* frame_crypto_group_bin_0322 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{24, {.type = CDL_FrameCap, .obj_id = 76 /* frame_crypto_group_bin_0081 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{25, {.type = CDL_FrameCap, .obj_id = 81 /* frame_crypto_group_bin_0087 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{26, {.type = CDL_FrameCap, .obj_id = 232 /* frame_crypto_group_bin_0250 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{27, {.type = CDL_FrameCap, .obj_id = 231 /* frame_crypto_group_bin_0249 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{28, {.type = CDL_FrameCap, .obj_id = 8 /* frame_crypto_group_bin_0004 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{29, {.type = CDL_FrameCap, .obj_id = 164 /* frame_crypto_group_bin_0178 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{30, {.type = CDL_FrameCap, .obj_id = 240 /* frame_crypto_group_bin_0259 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{31, {.type = CDL_FrameCap, .obj_id = 21 /* frame_crypto_group_bin_0017 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{32, {.type = CDL_FrameCap, .obj_id = 96 /* frame_crypto_group_bin_0102 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{33, {.type = CDL_FrameCap, .obj_id = 172 /* frame_crypto_group_bin_0187 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{34, {.type = CDL_FrameCap, .obj_id = 249 /* frame_crypto_group_bin_0268 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{35, {.type = CDL_FrameCap, .obj_id = 30 /* frame_crypto_group_bin_0026 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{36, {.type = CDL_FrameCap, .obj_id = 106 /* frame_crypto_group_bin_0115 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{37, {.type = CDL_FrameCap, .obj_id = 182 /* frame_crypto_group_bin_0197 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{38, {.type = CDL_FrameCap, .obj_id = 259 /* frame_crypto_group_bin_0278 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{39, {.type = CDL_FrameCap, .obj_id = 39 /* frame_crypto_group_bin_0038 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{40, {.type = CDL_FrameCap, .obj_id = 115 /* frame_crypto_group_bin_0124 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{41, {.type = CDL_FrameCap, .obj_id = 192 /* frame_crypto_group_bin_0207 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{42, {.type = CDL_FrameCap, .obj_id = 270 /* frame_crypto_group_bin_0290 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{43, {.type = CDL_FrameCap, .obj_id = 47 /* frame_crypto_group_bin_0047 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{44, {.type = CDL_FrameCap, .obj_id = 125 /* frame_crypto_group_bin_0134 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{45, {.type = CDL_FrameCap, .obj_id = 201 /* frame_crypto_group_bin_0216 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{46, {.type = CDL_FrameCap, .obj_id = 280 /* frame_crypto_group_bin_0300 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{47, {.type = CDL_FrameCap, .obj_id = 57 /* frame_crypto_group_bin_0058 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{48, {.type = CDL_FrameCap, .obj_id = 134 /* frame_crypto_group_bin_0144 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{49, {.type = CDL_FrameCap, .obj_id = 209 /* frame_crypto_group_bin_0225 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{50, {.type = CDL_FrameCap, .obj_id = 289 /* frame_crypto_group_bin_0310 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{51, {.type = CDL_FrameCap, .obj_id = 65 /* frame_crypto_group_bin_0068 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{52, {.type = CDL_FrameCap, .obj_id = 143 /* frame_crypto_group_bin_0154 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{53, {.type = CDL_FrameCap, .obj_id = 218 /* frame_crypto_group_bin_0235 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{54, {.type = CDL_FrameCap, .obj_id = 297 /* frame_crypto_group_bin_0320 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{55, {.type = CDL_FrameCap, .obj_id = 74 /* frame_crypto_group_bin_0078 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{56, {.type = CDL_FrameCap, .obj_id = 152 /* frame_crypto_group_bin_0164 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{57, {.type = CDL_FrameCap, .obj_id = 230 /* frame_crypto_group_bin_0247 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{58, {.type = CDL_FrameCap, .obj_id = 156 /* frame_crypto_group_bin_0168 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{59, {.type = CDL_FrameCap, .obj_id = 84 /* frame_crypto_group_bin_0090 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{60, {.type = CDL_FrameCap, .obj_id = 162 /* frame_crypto_group_bin_0175 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{61, {.type = CDL_FrameCap, .obj_id = 238 /* frame_crypto_group_bin_0257 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{62, {.type = CDL_FrameCap, .obj_id = 19 /* frame_crypto_group_bin_0015 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{63, {.type = CDL_FrameCap, .obj_id = 93 /* frame_crypto_group_bin_0099 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{64, {.type = CDL_FrameCap, .obj_id = 170 /* frame_crypto_group_bin_0185 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{65, {.type = CDL_FrameCap, .obj_id = 247 /* frame_crypto_group_bin_0266 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{66, {.type = CDL_FrameCap, .obj_id = 27 /* frame_crypto_group_bin_0023 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{67, {.type = CDL_FrameCap, .obj_id = 104 /* frame_crypto_group_bin_0112 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{68, {.type = CDL_FrameCap, .obj_id = 179 /* frame_crypto_group_bin_0194 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{69, {.type = CDL_FrameCap, .obj_id = 257 /* frame_crypto_group_bin_0276 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{70, {.type = CDL_FrameCap, .obj_id = 37 /* frame_crypto_group_bin_0035 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{71, {.type = CDL_FrameCap, .obj_id = 113 /* frame_crypto_group_bin_0122 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{72, {.type = CDL_FrameCap, .obj_id = 189 /* frame_crypto_group_bin_0204 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{73, {.type = CDL_FrameCap, .obj_id = 267 /* frame_crypto_group_bin_0286 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{74, {.type = CDL_FrameCap, .obj_id = 45 /* frame_crypto_group_bin_0045 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{75, {.type = CDL_FrameCap, .obj_id = 122 /* frame_crypto_group_bin_0131 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{76, {.type = CDL_FrameCap, .obj_id = 198 /* frame_crypto_group_bin_0213 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{77, {.type = CDL_FrameCap, .obj_id = 277 /* frame_crypto_group_bin_0297 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{78, {.type = CDL_FrameCap, .obj_id = 54 /* frame_crypto_group_bin_0055 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{79, {.type = CDL_FrameCap, .obj_id = 132 /* frame_crypto_group_bin_0142 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{80, {.type = CDL_FrameCap, .obj_id = 207 /* frame_crypto_group_bin_0223 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{81, {.type = CDL_FrameCap, .obj_id = 286 /* frame_crypto_group_bin_0307 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{82, {.type = CDL_FrameCap, .obj_id = 63 /* frame_crypto_group_bin_0065 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{83, {.type = CDL_FrameCap, .obj_id = 140 /* frame_crypto_group_bin_0151 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{84, {.type = CDL_FrameCap, .obj_id = 215 /* frame_crypto_group_bin_0232 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{85, {.type = CDL_FrameCap, .obj_id = 295 /* frame_crypto_group_bin_0317 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{86, {.type = CDL_FrameCap, .obj_id = 71 /* frame_crypto_group_bin_0075 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{87, {.type = CDL_FrameCap, .obj_id = 150 /* frame_crypto_group_bin_0162 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{88, {.type = CDL_FrameCap, .obj_id = 227 /* frame_crypto_group_bin_0244 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{89, {.type = CDL_FrameCap, .obj_id = 6 /* frame_crypto_group_bin_0002 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{90, {.type = CDL_FrameCap, .obj_id = 82 /* frame_crypto_group_bin_0088 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{91, {.type = CDL_FrameCap, .obj_id = 159 /* frame_crypto_group_bin_0171 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{92, {.type = CDL_FrameCap, .obj_id = 237 /* frame_crypto_group_bin_0256 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{93, {.type = CDL_FrameCap, .obj_id = 17 /* frame_crypto_group_bin_0013 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{94, {.type = CDL_FrameCap, .obj_id = 91 /* frame_crypto_group_bin_0097 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{95, {.type = CDL_FrameCap, .obj_id = 169 /* frame_crypto_group_bin_0184 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{96, {.type = CDL_FrameCap, .obj_id = 245 /* frame_crypto_group_bin_0264 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{97, {.type = CDL_FrameCap, .obj_id = 26 /* frame_crypto_group_bin_0022 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{98, {.type = CDL_FrameCap, .obj_id = 101 /* frame_crypto_group_bin_0108 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{99, {.type = CDL_FrameCap, .obj_id = 178 /* frame_crypto_group_bin_0193 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{100, {.type = CDL_FrameCap, .obj_id = 254 /* frame_crypto_group_bin_0273 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{101, {.type = CDL_FrameCap, .obj_id = 35 /* frame_crypto_group_bin_0031 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{102, {.type = CDL_FrameCap, .obj_id = 111 /* frame_crypto_group_bin_0120 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{103, {.type = CDL_FrameCap, .obj_id = 187 /* frame_crypto_group_bin_0202 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{104, {.type = CDL_FrameCap, .obj_id = 264 /* frame_crypto_group_bin_0283 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{105, {.type = CDL_FrameCap, .obj_id = 43 /* frame_crypto_group_bin_0043 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{106, {.type = CDL_FrameCap, .obj_id = 119 /* frame_crypto_group_bin_0128 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{107, {.type = CDL_FrameCap, .obj_id = 196 /* frame_crypto_group_bin_0211 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{108, {.type = CDL_FrameCap, .obj_id = 275 /* frame_crypto_group_bin_0295 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{109, {.type = CDL_FrameCap, .obj_id = 51 /* frame_crypto_group_bin_0052 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{110, {.type = CDL_FrameCap, .obj_id = 130 /* frame_crypto_group_bin_0140 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{111, {.type = CDL_FrameCap, .obj_id = 205 /* frame_crypto_group_bin_0221 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{112, {.type = CDL_FrameCap, .obj_id = 284 /* frame_crypto_group_bin_0305 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{113, {.type = CDL_FrameCap, .obj_id = 61 /* frame_crypto_group_bin_0062 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{114, {.type = CDL_FrameCap, .obj_id = 138 /* frame_crypto_group_bin_0148 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{115, {.type = CDL_FrameCap, .obj_id = 213 /* frame_crypto_group_bin_0230 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{116, {.type = CDL_FrameCap, .obj_id = 293 /* frame_crypto_group_bin_0314 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{117, {.type = CDL_FrameCap, .obj_id = 69 /* frame_crypto_group_bin_0073 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{118, {.type = CDL_FrameCap, .obj_id = 147 /* frame_crypto_group_bin_0159 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{119, {.type = CDL_FrameCap, .obj_id = 224 /* frame_crypto_group_bin_0241 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{120, {.type = CDL_FrameCap, .obj_id = 301 /* frame_crypto_group_bin_0324 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{121, {.type = CDL_FrameCap, .obj_id = 78 /* frame_crypto_group_bin_0084 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{122, {.type = CDL_FrameCap, .obj_id = 157 /* frame_crypto_group_bin_0169 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{123, {.type = CDL_FrameCap, .obj_id = 235 /* frame_crypto_group_bin_0253 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{124, {.type = CDL_FrameCap, .obj_id = 15 /* frame_crypto_group_bin_0011 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{125, {.type = CDL_FrameCap, .obj_id = 89 /* frame_crypto_group_bin_0095 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{126, {.type = CDL_FrameCap, .obj_id = 167 /* frame_crypto_group_bin_0181 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{127, {.type = CDL_FrameCap, .obj_id = 243 /* frame_crypto_group_bin_0262 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{128, {.type = CDL_FrameCap, .obj_id = 24 /* frame_crypto_group_bin_0020 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{129, {.type = CDL_FrameCap, .obj_id = 98 /* frame_crypto_group_bin_0105 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{130, {.type = CDL_FrameCap, .obj_id = 52 /* frame_crypto_group_bin_0053 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{131, {.type = CDL_FrameCap, .obj_id = 139 /* frame_crypto_group_bin_0149 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{132, {.type = CDL_FrameCap, .obj_id = 225 /* frame_crypto_group_bin_0242 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{133, {.type = CDL_FrameCap, .obj_id = 16 /* frame_crypto_group_bin_0012 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{134, {.type = CDL_FrameCap, .obj_id = 99 /* frame_crypto_group_bin_0106 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{135, {.type = CDL_FrameCap, .obj_id = 185 /* frame_crypto_group_bin_0200 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{136, {.type = CDL_FrameCap, .obj_id = 274 /* frame_crypto_group_bin_0294 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{137, {.type = CDL_FrameCap, .obj_id = 60 /* frame_crypto_group_bin_0061 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{138, {.type = CDL_FrameCap, .obj_id = 146 /* frame_crypto_group_bin_0158 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{139, {.type = CDL_FrameCap, .obj_id = 233 /* frame_crypto_group_bin_0251 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{140, {.type = CDL_FrameCap, .obj_id = 22 /* frame_crypto_group_bin_0018 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{141, {.type = CDL_FrameCap, .obj_id = 108 /* frame_crypto_group_bin_0117 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{142, {.type = CDL_FrameCap, .obj_id = 193 /* frame_crypto_group_bin_0208 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{143, {.type = CDL_FrameCap, .obj_id = 281 /* frame_crypto_group_bin_0301 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{144, {.type = CDL_FrameCap, .obj_id = 66 /* frame_crypto_group_bin_0070 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{145, {.type = CDL_FrameCap, .obj_id = 153 /* frame_crypto_group_bin_0165 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{146, {.type = CDL_FrameCap, .obj_id = 239 /* frame_crypto_group_bin_0258 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{147, {.type = CDL_FrameCap, .obj_id = 29 /* frame_crypto_group_bin_0025 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{148, {.type = CDL_FrameCap, .obj_id = 114 /* frame_crypto_group_bin_0123 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{149, {.type = CDL_FrameCap, .obj_id = 200 /* frame_crypto_group_bin_0215 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{150, {.type = CDL_FrameCap, .obj_id = 288 /* frame_crypto_group_bin_0309 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{151, {.type = CDL_FrameCap, .obj_id = 73 /* frame_crypto_group_bin_0077 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{152, {.type = CDL_FrameCap, .obj_id = 199 /* frame_crypto_group_bin_0214 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{153, {.type = CDL_FrameCap, .obj_id = 154 /* frame_crypto_group_bin_0166 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{154, {.type = CDL_FrameCap, .obj_id = 168 /* frame_crypto_group_bin_0182 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{155, {.type = CDL_FrameCap, .obj_id = 12 /* frame_crypto_group_bin_0008 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{156, {.type = CDL_FrameCap, .obj_id = 86 /* frame_crypto_group_bin_0092 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{157, {.type = CDL_FrameCap, .obj_id = 268 /* frame_crypto_group_bin_0287 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{158, {.type = CDL_FrameCap, .obj_id = 102 /* frame_crypto_group_bin_0109 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{159, {.type = CDL_FrameCap, .obj_id = 236 /* frame_crypto_group_bin_0254 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{160, {.type = CDL_FrameCap, .obj_id = 255 /* frame_crypto_group_bin_0274 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{161, {.type = CDL_FrameCap, .obj_id = 44 /* frame_crypto_group_bin_0044 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{162, {.type = CDL_FrameCap, .obj_id = 131 /* frame_crypto_group_bin_0141 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{163, {.type = CDL_FrameCap, .obj_id = 214 /* frame_crypto_group_bin_0231 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{164, {.type = CDL_FrameCap, .obj_id = 7 /* frame_crypto_group_bin_0003 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{165, {.type = CDL_FrameCap, .obj_id = 90 /* frame_crypto_group_bin_0096 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{166, {.type = CDL_FrameCap, .obj_id = 176 /* frame_crypto_group_bin_0191 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{167, {.type = CDL_FrameCap, .obj_id = 263 /* frame_crypto_group_bin_0282 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{168, {.type = CDL_FrameCap, .obj_id = 50 /* frame_crypto_group_bin_0051 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{169, {.type = CDL_FrameCap, .obj_id = 137 /* frame_crypto_group_bin_0147 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{170, {.type = CDL_FrameCap, .obj_id = 223 /* frame_crypto_group_bin_0240 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{171, {.type = CDL_FrameCap, .obj_id = 14 /* frame_crypto_group_bin_0010 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{172, {.type = CDL_FrameCap, .obj_id = 97 /* frame_crypto_group_bin_0104 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{173, {.type = CDL_FrameCap, .obj_id = 183 /* frame_crypto_group_bin_0198 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{174, {.type = CDL_FrameCap, .obj_id = 271 /* frame_crypto_group_bin_0291 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{175, {.type = CDL_FrameCap, .obj_id = 58 /* frame_crypto_group_bin_0059 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{176, {.type = CDL_FrameCap, .obj_id = 144 /* frame_crypto_group_bin_0155 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{177, {.type = CDL_FrameCap, .obj_id = 33 /* frame_crypto_group_bin_0029 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{178, {.type = CDL_FrameCap, .obj_id = 20 /* frame_crypto_group_bin_0016 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{179, {.type = CDL_FrameCap, .obj_id = 105 /* frame_crypto_group_bin_0114 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{180, {.type = CDL_FrameCap, .obj_id = 191 /* frame_crypto_group_bin_0206 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{181, {.type = CDL_FrameCap, .obj_id = 279 /* frame_crypto_group_bin_0299 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{182, {.type = CDL_FrameCap, .obj_id = 64 /* frame_crypto_group_bin_0067 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{183, {.type = CDL_FrameCap, .obj_id = 151 /* frame_crypto_group_bin_0163 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{184, {.type = CDL_FrameCap, .obj_id = 287 /* frame_crypto_group_bin_0308 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{185, {.type = CDL_FrameCap, .obj_id = 120 /* frame_crypto_group_bin_0129 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{186, {.type = CDL_FrameCap, .obj_id = 9 /* frame_crypto_group_bin_0005 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{187, {.type = CDL_FrameCap, .obj_id = 87 /* frame_crypto_group_bin_0093 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{188, {.type = CDL_FrameCap, .obj_id = 219 /* frame_crypto_group_bin_0236 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{189, {.type = CDL_FrameCap, .obj_id = 55 /* frame_crypto_group_bin_0056 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{190, {.type = CDL_FrameCap, .obj_id = 188 /* frame_crypto_group_bin_0203 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{191, {.type = CDL_FrameCap, .obj_id = 25 /* frame_crypto_group_bin_0021 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{192, {.type = CDL_FrameCap, .obj_id = 36 /* frame_crypto_group_bin_0032 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{193, {.type = CDL_FrameCap, .obj_id = 292 /* frame_crypto_group_bin_0313 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{194, {.type = CDL_FrameCap, .obj_id = 206 /* frame_crypto_group_bin_0222 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{195, {.type = CDL_FrameCap, .obj_id = 294 /* frame_crypto_group_bin_0315 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{196, {.type = CDL_FrameCap, .obj_id = 79 /* frame_crypto_group_bin_0085 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{197, {.type = CDL_FrameCap, .obj_id = 226 /* frame_crypto_group_bin_0243 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{198, {.type = CDL_FrameCap, .obj_id = 253 /* frame_crypto_group_bin_0272 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{199, {.type = CDL_FrameCap, .obj_id = 42 /* frame_crypto_group_bin_0042 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{200, {.type = CDL_FrameCap, .obj_id = 129 /* frame_crypto_group_bin_0139 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{201, {.type = CDL_FrameCap, .obj_id = 212 /* frame_crypto_group_bin_0229 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{202, {.type = CDL_FrameCap, .obj_id = 300 /* frame_crypto_group_bin_0323 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{203, {.type = CDL_FrameCap, .obj_id = 88 /* frame_crypto_group_bin_0094 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{204, {.type = CDL_FrameCap, .obj_id = 174 /* frame_crypto_group_bin_0189 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{205, {.type = CDL_FrameCap, .obj_id = 261 /* frame_crypto_group_bin_0280 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{206, {.type = CDL_FrameCap, .obj_id = 48 /* frame_crypto_group_bin_0048 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{207, {.type = CDL_FrameCap, .obj_id = 135 /* frame_crypto_group_bin_0145 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{208, {.type = CDL_FrameCap, .obj_id = 221 /* frame_crypto_group_bin_0238 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{209, {.type = CDL_FrameCap, .obj_id = 11 /* frame_crypto_group_bin_0007 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{210, {.type = CDL_FrameCap, .obj_id = 95 /* frame_crypto_group_bin_0101 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{211, {.type = CDL_FrameCap, .obj_id = 181 /* frame_crypto_group_bin_0196 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{212, {.type = CDL_FrameCap, .obj_id = 269 /* frame_crypto_group_bin_0289 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{213, {.type = CDL_FrameCap, .obj_id = 56 /* frame_crypto_group_bin_0057 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{214, {.type = CDL_FrameCap, .obj_id = 142 /* frame_crypto_group_bin_0153 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{215, {.type = CDL_FrameCap, .obj_id = 229 /* frame_crypto_group_bin_0246 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{216, {.type = CDL_FrameCap, .obj_id = 72 /* frame_crypto_group_bin_0076 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{217, {.type = CDL_FrameCap, .obj_id = 123 /* frame_crypto_group_bin_0132 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{218, {.type = CDL_FrameCap, .obj_id = 190 /* frame_crypto_group_bin_0205 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{219, {.type = CDL_FrameCap, .obj_id = 173 /* frame_crypto_group_bin_0188 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{220, {.type = CDL_FrameCap, .obj_id = 10 /* frame_crypto_group_bin_0006 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{221, {.type = CDL_FrameCap, .obj_id = 141 /* frame_crypto_group_bin_0152 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{222, {.type = CDL_FrameCap, .obj_id = 276 /* frame_crypto_group_bin_0296 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{223, {.type = CDL_FrameCap, .obj_id = 110 /* frame_crypto_group_bin_0119 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{224, {.type = CDL_FrameCap, .obj_id = 112 /* frame_crypto_group_bin_0121 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{225, {.type = CDL_FrameCap, .obj_id = 197 /* frame_crypto_group_bin_0212 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{226, {.type = CDL_FrameCap, .obj_id = 285 /* frame_crypto_group_bin_0306 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{227, {.type = CDL_FrameCap, .obj_id = 70 /* frame_crypto_group_bin_0074 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{228, {.type = CDL_FrameCap, .obj_id = 158 /* frame_crypto_group_bin_0170 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{229, {.type = CDL_FrameCap, .obj_id = 244 /* frame_crypto_group_bin_0263 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{230, {.type = CDL_FrameCap, .obj_id = 121 /* frame_crypto_group_bin_0130 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{231, {.type = CDL_FrameCap, .obj_id = 118 /* frame_crypto_group_bin_0127 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{232, {.type = CDL_FrameCap, .obj_id = 204 /* frame_crypto_group_bin_0219 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{233, {.type = CDL_FrameCap, .obj_id = 248 /* frame_crypto_group_bin_0267 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{234, {.type = CDL_FrameCap, .obj_id = 77 /* frame_crypto_group_bin_0083 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{235, {.type = CDL_FrameCap, .obj_id = 165 /* frame_crypto_group_bin_0179 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{236, {.type = CDL_FrameCap, .obj_id = 250 /* frame_crypto_group_bin_0269 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{237, {.type = CDL_FrameCap, .obj_id = 40 /* frame_crypto_group_bin_0039 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{238, {.type = CDL_FrameCap, .obj_id = 126 /* frame_crypto_group_bin_0136 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{239, {.type = CDL_FrameCap, .obj_id = 210 /* frame_crypto_group_bin_0226 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{240, {.type = CDL_FrameCap, .obj_id = 298 /* frame_crypto_group_bin_0321 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{241, {.type = CDL_FrameCap, .obj_id = 85 /* frame_crypto_group_bin_0091 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{242, {.type = CDL_FrameCap, .obj_id = 171 /* frame_crypto_group_bin_0186 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{243, {.type = CDL_FrameCap, .obj_id = 258 /* frame_crypto_group_bin_0277 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{244, {.type = CDL_FrameCap, .obj_id = 46 /* frame_crypto_group_bin_0046 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{245, {.type = CDL_FrameCap, .obj_id = 133 /* frame_crypto_group_bin_0143 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{246, {.type = CDL_FrameCap, .obj_id = 217 /* frame_crypto_group_bin_0234 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{247, {.type = CDL_FrameCap, .obj_id = 107 /* frame_crypto_group_bin_0116 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{248, {.type = CDL_FrameCap, .obj_id = 160 /* frame_crypto_group_bin_0172 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{249, {.type = CDL_FrameCap, .obj_id = 256 /* frame_crypto_group_bin_0275 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{250, {.type = CDL_FrameCap, .obj_id = 128 /* frame_crypto_group_bin_0138 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{251, {.type = CDL_FrameCap, .obj_id = 260 /* frame_crypto_group_bin_0279 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{252, {.type = CDL_FrameCap, .obj_id = 94 /* frame_crypto_group_bin_0100 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{253, {.type = CDL_FrameCap, .obj_id = 228 /* frame_crypto_group_bin_0245 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{254, {.type = CDL_FrameCap, .obj_id = 62 /* frame_crypto_group_bin_0063 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{255, {.type = CDL_FrameCap, .obj_id = 195 /* frame_crypto_group_bin_0210 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{256, {.type = CDL_FrameCap, .obj_id = 34 /* frame_crypto_group_bin_0030 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{257, {.type = CDL_FrameCap, .obj_id = 166 /* frame_crypto_group_bin_0180 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{258, {.type = CDL_FrameCap, .obj_id = 216 /* frame_crypto_group_bin_0233 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{259, {.type = CDL_FrameCap, .obj_id = 148 /* frame_crypto_group_bin_0160 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{260, {.type = CDL_FrameCap, .obj_id = 266 /* frame_crypto_group_bin_0285 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{261, {.type = CDL_FrameCap, .obj_id = 100 /* frame_crypto_group_bin_0107 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{262, {.type = CDL_FrameCap, .obj_id = 234 /* frame_crypto_group_bin_0252 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{263, {.type = CDL_FrameCap, .obj_id = 278 /* frame_crypto_group_bin_0298 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{264, {.type = CDL_FrameCap, .obj_id = 283 /* frame_crypto_group_bin_0304 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{265, {.type = CDL_FrameCap, .obj_id = 68 /* frame_crypto_group_bin_0072 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{266, {.type = CDL_FrameCap, .obj_id = 155 /* frame_crypto_group_bin_0167 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{267, {.type = CDL_FrameCap, .obj_id = 242 /* frame_crypto_group_bin_0261 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{268, {.type = CDL_FrameCap, .obj_id = 31 /* frame_crypto_group_bin_0027 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{269, {.type = CDL_FrameCap, .obj_id = 116 /* frame_crypto_group_bin_0125 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{270, {.type = CDL_FrameCap, .obj_id = 202 /* frame_crypto_group_bin_0217 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{271, {.type = CDL_FrameCap, .obj_id = 290 /* frame_crypto_group_bin_0311 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{272, {.type = CDL_FrameCap, .obj_id = 75 /* frame_crypto_group_bin_0080 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{273, {.type = CDL_FrameCap, .obj_id = 163 /* frame_crypto_group_bin_0177 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{274, {.type = CDL_FrameCap, .obj_id = 103 /* frame_crypto_group_bin_0111 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{275, {.type = CDL_FrameCap, .obj_id = 38 /* frame_crypto_group_bin_0037 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{276, {.type = CDL_FrameCap, .obj_id = 124 /* frame_crypto_group_bin_0133 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{277, {.type = CDL_FrameCap, .obj_id = 208 /* frame_crypto_group_bin_0224 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{278, {.type = CDL_FrameCap, .obj_id = 296 /* frame_crypto_group_bin_0319 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{279, {.type = CDL_FrameCap, .obj_id = 83 /* frame_crypto_group_bin_0089 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{280, {.type = CDL_FrameCap, .obj_id = 246 /* frame_crypto_group_bin_0265 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{281, {.type = CDL_FrameCap, .obj_id = 80 /* frame_crypto_group_bin_0086 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{282, {.type = CDL_FrameCap, .obj_id = 161 /* frame_crypto_group_bin_0174 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{283, {.type = CDL_FrameCap, .obj_id = 92 /* frame_crypto_group_bin_0098 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{284, {.type = CDL_FrameCap, .obj_id = 180 /* frame_crypto_group_bin_0195 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{285, {.type = CDL_FrameCap, .obj_id = 18 /* frame_crypto_group_bin_0014 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{286, {.type = CDL_FrameCap, .obj_id = 149 /* frame_crypto_group_bin_0161 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{287, {.type = CDL_FrameCap, .obj_id = 177 /* frame_crypto_group_bin_0192 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{288, {.type = CDL_FrameCap, .obj_id = 265 /* frame_crypto_group_bin_0284 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{289, {.type = CDL_FrameCap, .obj_id = 251 /* frame_crypto_group_bin_0270 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{290, {.type = CDL_FrameCap, .obj_id = 220 /* frame_crypto_group_bin_0237 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{291, {.type = CDL_FrameCap, .obj_id = 28 /* frame_crypto_group_bin_0024 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{292, {.type = CDL_FrameCap, .obj_id = 53 /* frame_crypto_group_bin_0054 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{293, {.type = CDL_FrameCap, .obj_id = 186 /* frame_crypto_group_bin_0201 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{294, {.type = CDL_FrameCap, .obj_id = 23 /* frame_crypto_group_bin_0019 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{295, {.type = CDL_FrameCap, .obj_id = 273 /* frame_crypto_group_bin_0293 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{296, {.type = CDL_FrameCap, .obj_id = 241 /* frame_crypto_group_bin_0260 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{297, {.type = CDL_FrameCap, .obj_id = 13 /* frame_crypto_group_bin_0009 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{299, {.type = CDL_FrameCap, .obj_id = 1217 /* stack__camkes_stack_crypto_0_control_0_crypto_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{300, {.type = CDL_FrameCap, .obj_id = 1218 /* stack__camkes_stack_crypto_0_control_1_crypto_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{301, {.type = CDL_FrameCap, .obj_id = 1219 /* stack__camkes_stack_crypto_0_control_2_crypto_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{302, {.type = CDL_FrameCap, .obj_id = 1220 /* stack__camkes_stack_crypto_0_control_3_crypto_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{305, {.type = CDL_FrameCap, .obj_id = 1225 /* stack__camkes_stack_crypto_crypto_iface_0000_0_crypto_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{306, {.type = CDL_FrameCap, .obj_id = 1226 /* stack__camkes_stack_crypto_crypto_iface_0000_1_crypto_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{307, {.type = CDL_FrameCap, .obj_id = 1227 /* stack__camkes_stack_crypto_crypto_iface_0000_2_crypto_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{308, {.type = CDL_FrameCap, .obj_id = 1228 /* stack__camkes_stack_crypto_crypto_iface_0000_3_crypto_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{311, {.type = CDL_FrameCap, .obj_id = 1221 /* stack__camkes_stack_crypto_0_fault_handler_0000_0_crypto_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{312, {.type = CDL_FrameCap, .obj_id = 1222 /* stack__camkes_stack_crypto_0_fault_handler_0000_1_crypto_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{313, {.type = CDL_FrameCap, .obj_id = 1223 /* stack__camkes_stack_crypto_0_fault_handler_0000_2_crypto_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{314, {.type = CDL_FrameCap, .obj_id = 1224 /* stack__camkes_stack_crypto_0_fault_handler_0000_3_crypto_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{317, {.type = CDL_FrameCap, .obj_id = 0 /* crypto_frame__camkes_ipc_buffer_crypto_0_control */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{320, {.type = CDL_FrameCap, .obj_id = 2 /* crypto_frame__camkes_ipc_buffer_crypto_crypto_iface_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{323, {.type = CDL_FrameCap, .obj_id = 1 /* crypto_frame__camkes_ipc_buffer_crypto_0_fault_handler_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},

},
},
[1210] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "pt_modchk_group_bin_0002",
#endif
.type = CDL_PT,
.slots.num = 312,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_FrameCap, .obj_id = 302 /* frame_modchk_group_bin_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{1, {.type = CDL_FrameCap, .obj_id = 303 /* frame_modchk_group_bin_0001 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{2, {.type = CDL_FrameCap, .obj_id = 472 /* frame_modchk_group_bin_0189 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{3, {.type = CDL_FrameCap, .obj_id = 549 /* frame_modchk_group_bin_0270 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{4, {.type = CDL_FrameCap, .obj_id = 329 /* frame_modchk_group_bin_0028 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{5, {.type = CDL_FrameCap, .obj_id = 406 /* frame_modchk_group_bin_0118 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{6, {.type = CDL_FrameCap, .obj_id = 481 /* frame_modchk_group_bin_0198 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{7, {.type = CDL_FrameCap, .obj_id = 559 /* frame_modchk_group_bin_0280 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{8, {.type = CDL_FrameCap, .obj_id = 338 /* frame_modchk_group_bin_0041 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{9, {.type = CDL_FrameCap, .obj_id = 414 /* frame_modchk_group_bin_0126 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{10, {.type = CDL_FrameCap, .obj_id = 491 /* frame_modchk_group_bin_0208 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{11, {.type = CDL_FrameCap, .obj_id = 569 /* frame_modchk_group_bin_0291 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{12, {.type = CDL_FrameCap, .obj_id = 346 /* frame_modchk_group_bin_0049 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{13, {.type = CDL_FrameCap, .obj_id = 424 /* frame_modchk_group_bin_0137 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{14, {.type = CDL_FrameCap, .obj_id = 500 /* frame_modchk_group_bin_0217 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{15, {.type = CDL_FrameCap, .obj_id = 579 /* frame_modchk_group_bin_0301 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{16, {.type = CDL_FrameCap, .obj_id = 356 /* frame_modchk_group_bin_0060 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{17, {.type = CDL_FrameCap, .obj_id = 433 /* frame_modchk_group_bin_0146 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{18, {.type = CDL_FrameCap, .obj_id = 508 /* frame_modchk_group_bin_0226 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{19, {.type = CDL_FrameCap, .obj_id = 588 /* frame_modchk_group_bin_0311 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{20, {.type = CDL_FrameCap, .obj_id = 364 /* frame_modchk_group_bin_0071 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{21, {.type = CDL_FrameCap, .obj_id = 442 /* frame_modchk_group_bin_0155 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{22, {.type = CDL_FrameCap, .obj_id = 519 /* frame_modchk_group_bin_0238 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{23, {.type = CDL_FrameCap, .obj_id = 596 /* frame_modchk_group_bin_0321 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{24, {.type = CDL_FrameCap, .obj_id = 373 /* frame_modchk_group_bin_0081 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{25, {.type = CDL_FrameCap, .obj_id = 378 /* frame_modchk_group_bin_0087 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{26, {.type = CDL_FrameCap, .obj_id = 529 /* frame_modchk_group_bin_0249 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{27, {.type = CDL_FrameCap, .obj_id = 528 /* frame_modchk_group_bin_0248 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{28, {.type = CDL_FrameCap, .obj_id = 306 /* frame_modchk_group_bin_0004 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{29, {.type = CDL_FrameCap, .obj_id = 461 /* frame_modchk_group_bin_0177 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{30, {.type = CDL_FrameCap, .obj_id = 537 /* frame_modchk_group_bin_0258 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{31, {.type = CDL_FrameCap, .obj_id = 318 /* frame_modchk_group_bin_0017 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{32, {.type = CDL_FrameCap, .obj_id = 393 /* frame_modchk_group_bin_0102 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{33, {.type = CDL_FrameCap, .obj_id = 469 /* frame_modchk_group_bin_0186 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{34, {.type = CDL_FrameCap, .obj_id = 546 /* frame_modchk_group_bin_0267 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{35, {.type = CDL_FrameCap, .obj_id = 327 /* frame_modchk_group_bin_0026 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{36, {.type = CDL_FrameCap, .obj_id = 403 /* frame_modchk_group_bin_0115 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{37, {.type = CDL_FrameCap, .obj_id = 479 /* frame_modchk_group_bin_0196 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{38, {.type = CDL_FrameCap, .obj_id = 556 /* frame_modchk_group_bin_0277 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{39, {.type = CDL_FrameCap, .obj_id = 336 /* frame_modchk_group_bin_0038 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{40, {.type = CDL_FrameCap, .obj_id = 412 /* frame_modchk_group_bin_0124 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{41, {.type = CDL_FrameCap, .obj_id = 489 /* frame_modchk_group_bin_0206 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{42, {.type = CDL_FrameCap, .obj_id = 567 /* frame_modchk_group_bin_0289 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{43, {.type = CDL_FrameCap, .obj_id = 344 /* frame_modchk_group_bin_0047 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{44, {.type = CDL_FrameCap, .obj_id = 422 /* frame_modchk_group_bin_0134 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{45, {.type = CDL_FrameCap, .obj_id = 498 /* frame_modchk_group_bin_0215 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{46, {.type = CDL_FrameCap, .obj_id = 577 /* frame_modchk_group_bin_0299 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{47, {.type = CDL_FrameCap, .obj_id = 354 /* frame_modchk_group_bin_0058 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{48, {.type = CDL_FrameCap, .obj_id = 431 /* frame_modchk_group_bin_0144 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{49, {.type = CDL_FrameCap, .obj_id = 506 /* frame_modchk_group_bin_0224 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{50, {.type = CDL_FrameCap, .obj_id = 586 /* frame_modchk_group_bin_0309 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{51, {.type = CDL_FrameCap, .obj_id = 362 /* frame_modchk_group_bin_0068 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{52, {.type = CDL_FrameCap, .obj_id = 440 /* frame_modchk_group_bin_0153 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{53, {.type = CDL_FrameCap, .obj_id = 515 /* frame_modchk_group_bin_0234 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{54, {.type = CDL_FrameCap, .obj_id = 594 /* frame_modchk_group_bin_0319 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{55, {.type = CDL_FrameCap, .obj_id = 371 /* frame_modchk_group_bin_0078 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{56, {.type = CDL_FrameCap, .obj_id = 449 /* frame_modchk_group_bin_0163 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{57, {.type = CDL_FrameCap, .obj_id = 527 /* frame_modchk_group_bin_0246 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{58, {.type = CDL_FrameCap, .obj_id = 453 /* frame_modchk_group_bin_0167 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{59, {.type = CDL_FrameCap, .obj_id = 381 /* frame_modchk_group_bin_0090 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{60, {.type = CDL_FrameCap, .obj_id = 459 /* frame_modchk_group_bin_0174 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{61, {.type = CDL_FrameCap, .obj_id = 535 /* frame_modchk_group_bin_0256 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{62, {.type = CDL_FrameCap, .obj_id = 316 /* frame_modchk_group_bin_0015 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{63, {.type = CDL_FrameCap, .obj_id = 390 /* frame_modchk_group_bin_0099 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{64, {.type = CDL_FrameCap, .obj_id = 467 /* frame_modchk_group_bin_0184 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{65, {.type = CDL_FrameCap, .obj_id = 544 /* frame_modchk_group_bin_0265 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{66, {.type = CDL_FrameCap, .obj_id = 324 /* frame_modchk_group_bin_0023 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{67, {.type = CDL_FrameCap, .obj_id = 401 /* frame_modchk_group_bin_0112 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{68, {.type = CDL_FrameCap, .obj_id = 476 /* frame_modchk_group_bin_0193 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{69, {.type = CDL_FrameCap, .obj_id = 554 /* frame_modchk_group_bin_0275 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{70, {.type = CDL_FrameCap, .obj_id = 334 /* frame_modchk_group_bin_0035 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{71, {.type = CDL_FrameCap, .obj_id = 410 /* frame_modchk_group_bin_0122 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{72, {.type = CDL_FrameCap, .obj_id = 486 /* frame_modchk_group_bin_0203 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{73, {.type = CDL_FrameCap, .obj_id = 564 /* frame_modchk_group_bin_0285 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{74, {.type = CDL_FrameCap, .obj_id = 342 /* frame_modchk_group_bin_0045 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{75, {.type = CDL_FrameCap, .obj_id = 419 /* frame_modchk_group_bin_0131 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{76, {.type = CDL_FrameCap, .obj_id = 495 /* frame_modchk_group_bin_0212 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{77, {.type = CDL_FrameCap, .obj_id = 574 /* frame_modchk_group_bin_0296 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{78, {.type = CDL_FrameCap, .obj_id = 351 /* frame_modchk_group_bin_0055 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{79, {.type = CDL_FrameCap, .obj_id = 429 /* frame_modchk_group_bin_0142 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{80, {.type = CDL_FrameCap, .obj_id = 504 /* frame_modchk_group_bin_0222 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{81, {.type = CDL_FrameCap, .obj_id = 583 /* frame_modchk_group_bin_0306 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{82, {.type = CDL_FrameCap, .obj_id = 360 /* frame_modchk_group_bin_0065 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{83, {.type = CDL_FrameCap, .obj_id = 437 /* frame_modchk_group_bin_0150 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{84, {.type = CDL_FrameCap, .obj_id = 512 /* frame_modchk_group_bin_0231 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{85, {.type = CDL_FrameCap, .obj_id = 592 /* frame_modchk_group_bin_0316 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{86, {.type = CDL_FrameCap, .obj_id = 368 /* frame_modchk_group_bin_0075 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{87, {.type = CDL_FrameCap, .obj_id = 447 /* frame_modchk_group_bin_0161 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{88, {.type = CDL_FrameCap, .obj_id = 524 /* frame_modchk_group_bin_0243 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{89, {.type = CDL_FrameCap, .obj_id = 304 /* frame_modchk_group_bin_0002 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{90, {.type = CDL_FrameCap, .obj_id = 379 /* frame_modchk_group_bin_0088 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{91, {.type = CDL_FrameCap, .obj_id = 456 /* frame_modchk_group_bin_0170 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{92, {.type = CDL_FrameCap, .obj_id = 534 /* frame_modchk_group_bin_0255 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{93, {.type = CDL_FrameCap, .obj_id = 314 /* frame_modchk_group_bin_0013 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{94, {.type = CDL_FrameCap, .obj_id = 388 /* frame_modchk_group_bin_0097 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{95, {.type = CDL_FrameCap, .obj_id = 466 /* frame_modchk_group_bin_0183 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{96, {.type = CDL_FrameCap, .obj_id = 542 /* frame_modchk_group_bin_0263 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{97, {.type = CDL_FrameCap, .obj_id = 323 /* frame_modchk_group_bin_0022 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{98, {.type = CDL_FrameCap, .obj_id = 398 /* frame_modchk_group_bin_0108 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{99, {.type = CDL_FrameCap, .obj_id = 475 /* frame_modchk_group_bin_0192 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{100, {.type = CDL_FrameCap, .obj_id = 551 /* frame_modchk_group_bin_0272 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{101, {.type = CDL_FrameCap, .obj_id = 332 /* frame_modchk_group_bin_0031 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{102, {.type = CDL_FrameCap, .obj_id = 408 /* frame_modchk_group_bin_0120 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{103, {.type = CDL_FrameCap, .obj_id = 484 /* frame_modchk_group_bin_0201 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{104, {.type = CDL_FrameCap, .obj_id = 561 /* frame_modchk_group_bin_0282 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{105, {.type = CDL_FrameCap, .obj_id = 340 /* frame_modchk_group_bin_0043 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{106, {.type = CDL_FrameCap, .obj_id = 416 /* frame_modchk_group_bin_0128 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{107, {.type = CDL_FrameCap, .obj_id = 493 /* frame_modchk_group_bin_0210 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{108, {.type = CDL_FrameCap, .obj_id = 572 /* frame_modchk_group_bin_0294 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{109, {.type = CDL_FrameCap, .obj_id = 348 /* frame_modchk_group_bin_0052 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{110, {.type = CDL_FrameCap, .obj_id = 427 /* frame_modchk_group_bin_0140 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{111, {.type = CDL_FrameCap, .obj_id = 502 /* frame_modchk_group_bin_0220 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{112, {.type = CDL_FrameCap, .obj_id = 581 /* frame_modchk_group_bin_0304 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{113, {.type = CDL_FrameCap, .obj_id = 358 /* frame_modchk_group_bin_0062 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{114, {.type = CDL_FrameCap, .obj_id = 435 /* frame_modchk_group_bin_0148 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{115, {.type = CDL_FrameCap, .obj_id = 510 /* frame_modchk_group_bin_0229 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{116, {.type = CDL_FrameCap, .obj_id = 590 /* frame_modchk_group_bin_0313 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{117, {.type = CDL_FrameCap, .obj_id = 366 /* frame_modchk_group_bin_0073 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{118, {.type = CDL_FrameCap, .obj_id = 444 /* frame_modchk_group_bin_0158 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{119, {.type = CDL_FrameCap, .obj_id = 521 /* frame_modchk_group_bin_0240 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{120, {.type = CDL_FrameCap, .obj_id = 598 /* frame_modchk_group_bin_0323 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{121, {.type = CDL_FrameCap, .obj_id = 375 /* frame_modchk_group_bin_0084 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{122, {.type = CDL_FrameCap, .obj_id = 454 /* frame_modchk_group_bin_0168 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{123, {.type = CDL_FrameCap, .obj_id = 532 /* frame_modchk_group_bin_0252 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{124, {.type = CDL_FrameCap, .obj_id = 312 /* frame_modchk_group_bin_0011 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{125, {.type = CDL_FrameCap, .obj_id = 386 /* frame_modchk_group_bin_0095 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{126, {.type = CDL_FrameCap, .obj_id = 464 /* frame_modchk_group_bin_0180 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{127, {.type = CDL_FrameCap, .obj_id = 540 /* frame_modchk_group_bin_0261 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{128, {.type = CDL_FrameCap, .obj_id = 321 /* frame_modchk_group_bin_0020 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{129, {.type = CDL_FrameCap, .obj_id = 395 /* frame_modchk_group_bin_0105 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{130, {.type = CDL_FrameCap, .obj_id = 349 /* frame_modchk_group_bin_0053 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{131, {.type = CDL_FrameCap, .obj_id = 436 /* frame_modchk_group_bin_0149 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{132, {.type = CDL_FrameCap, .obj_id = 522 /* frame_modchk_group_bin_0241 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{133, {.type = CDL_FrameCap, .obj_id = 313 /* frame_modchk_group_bin_0012 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{134, {.type = CDL_FrameCap, .obj_id = 396 /* frame_modchk_group_bin_0106 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{135, {.type = CDL_FrameCap, .obj_id = 482 /* frame_modchk_group_bin_0199 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{136, {.type = CDL_FrameCap, .obj_id = 571 /* frame_modchk_group_bin_0293 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{137, {.type = CDL_FrameCap, .obj_id = 357 /* frame_modchk_group_bin_0061 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{138, {.type = CDL_FrameCap, .obj_id = 443 /* frame_modchk_group_bin_0157 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{139, {.type = CDL_FrameCap, .obj_id = 530 /* frame_modchk_group_bin_0250 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{140, {.type = CDL_FrameCap, .obj_id = 319 /* frame_modchk_group_bin_0018 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{141, {.type = CDL_FrameCap, .obj_id = 405 /* frame_modchk_group_bin_0117 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{142, {.type = CDL_FrameCap, .obj_id = 490 /* frame_modchk_group_bin_0207 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{143, {.type = CDL_FrameCap, .obj_id = 578 /* frame_modchk_group_bin_0300 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{144, {.type = CDL_FrameCap, .obj_id = 363 /* frame_modchk_group_bin_0070 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{145, {.type = CDL_FrameCap, .obj_id = 450 /* frame_modchk_group_bin_0164 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{146, {.type = CDL_FrameCap, .obj_id = 536 /* frame_modchk_group_bin_0257 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{147, {.type = CDL_FrameCap, .obj_id = 326 /* frame_modchk_group_bin_0025 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{148, {.type = CDL_FrameCap, .obj_id = 411 /* frame_modchk_group_bin_0123 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{149, {.type = CDL_FrameCap, .obj_id = 497 /* frame_modchk_group_bin_0214 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{150, {.type = CDL_FrameCap, .obj_id = 585 /* frame_modchk_group_bin_0308 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{151, {.type = CDL_FrameCap, .obj_id = 370 /* frame_modchk_group_bin_0077 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{152, {.type = CDL_FrameCap, .obj_id = 496 /* frame_modchk_group_bin_0213 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{153, {.type = CDL_FrameCap, .obj_id = 451 /* frame_modchk_group_bin_0165 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{154, {.type = CDL_FrameCap, .obj_id = 465 /* frame_modchk_group_bin_0181 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{155, {.type = CDL_FrameCap, .obj_id = 310 /* frame_modchk_group_bin_0008 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{156, {.type = CDL_FrameCap, .obj_id = 383 /* frame_modchk_group_bin_0092 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{157, {.type = CDL_FrameCap, .obj_id = 565 /* frame_modchk_group_bin_0286 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{158, {.type = CDL_FrameCap, .obj_id = 399 /* frame_modchk_group_bin_0109 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{159, {.type = CDL_FrameCap, .obj_id = 533 /* frame_modchk_group_bin_0253 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{160, {.type = CDL_FrameCap, .obj_id = 552 /* frame_modchk_group_bin_0273 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{161, {.type = CDL_FrameCap, .obj_id = 341 /* frame_modchk_group_bin_0044 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{162, {.type = CDL_FrameCap, .obj_id = 428 /* frame_modchk_group_bin_0141 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{163, {.type = CDL_FrameCap, .obj_id = 511 /* frame_modchk_group_bin_0230 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{164, {.type = CDL_FrameCap, .obj_id = 305 /* frame_modchk_group_bin_0003 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{165, {.type = CDL_FrameCap, .obj_id = 387 /* frame_modchk_group_bin_0096 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{166, {.type = CDL_FrameCap, .obj_id = 473 /* frame_modchk_group_bin_0190 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{167, {.type = CDL_FrameCap, .obj_id = 560 /* frame_modchk_group_bin_0281 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{168, {.type = CDL_FrameCap, .obj_id = 347 /* frame_modchk_group_bin_0051 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{169, {.type = CDL_FrameCap, .obj_id = 434 /* frame_modchk_group_bin_0147 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{170, {.type = CDL_FrameCap, .obj_id = 520 /* frame_modchk_group_bin_0239 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{171, {.type = CDL_FrameCap, .obj_id = 311 /* frame_modchk_group_bin_0010 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{172, {.type = CDL_FrameCap, .obj_id = 394 /* frame_modchk_group_bin_0104 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{173, {.type = CDL_FrameCap, .obj_id = 480 /* frame_modchk_group_bin_0197 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{174, {.type = CDL_FrameCap, .obj_id = 568 /* frame_modchk_group_bin_0290 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{175, {.type = CDL_FrameCap, .obj_id = 355 /* frame_modchk_group_bin_0059 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{176, {.type = CDL_FrameCap, .obj_id = 441 /* frame_modchk_group_bin_0154 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{177, {.type = CDL_FrameCap, .obj_id = 330 /* frame_modchk_group_bin_0029 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{178, {.type = CDL_FrameCap, .obj_id = 317 /* frame_modchk_group_bin_0016 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{179, {.type = CDL_FrameCap, .obj_id = 402 /* frame_modchk_group_bin_0114 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{180, {.type = CDL_FrameCap, .obj_id = 488 /* frame_modchk_group_bin_0205 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{181, {.type = CDL_FrameCap, .obj_id = 576 /* frame_modchk_group_bin_0298 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{182, {.type = CDL_FrameCap, .obj_id = 361 /* frame_modchk_group_bin_0067 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{183, {.type = CDL_FrameCap, .obj_id = 448 /* frame_modchk_group_bin_0162 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{184, {.type = CDL_FrameCap, .obj_id = 584 /* frame_modchk_group_bin_0307 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{185, {.type = CDL_FrameCap, .obj_id = 417 /* frame_modchk_group_bin_0129 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{186, {.type = CDL_FrameCap, .obj_id = 307 /* frame_modchk_group_bin_0005 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{187, {.type = CDL_FrameCap, .obj_id = 384 /* frame_modchk_group_bin_0093 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{188, {.type = CDL_FrameCap, .obj_id = 516 /* frame_modchk_group_bin_0235 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{189, {.type = CDL_FrameCap, .obj_id = 352 /* frame_modchk_group_bin_0056 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{190, {.type = CDL_FrameCap, .obj_id = 485 /* frame_modchk_group_bin_0202 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{191, {.type = CDL_FrameCap, .obj_id = 322 /* frame_modchk_group_bin_0021 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{192, {.type = CDL_FrameCap, .obj_id = 333 /* frame_modchk_group_bin_0032 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{193, {.type = CDL_FrameCap, .obj_id = 589 /* frame_modchk_group_bin_0312 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{194, {.type = CDL_FrameCap, .obj_id = 503 /* frame_modchk_group_bin_0221 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{195, {.type = CDL_FrameCap, .obj_id = 591 /* frame_modchk_group_bin_0314 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{196, {.type = CDL_FrameCap, .obj_id = 376 /* frame_modchk_group_bin_0085 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{197, {.type = CDL_FrameCap, .obj_id = 523 /* frame_modchk_group_bin_0242 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{198, {.type = CDL_FrameCap, .obj_id = 550 /* frame_modchk_group_bin_0271 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{199, {.type = CDL_FrameCap, .obj_id = 339 /* frame_modchk_group_bin_0042 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{200, {.type = CDL_FrameCap, .obj_id = 426 /* frame_modchk_group_bin_0139 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{201, {.type = CDL_FrameCap, .obj_id = 509 /* frame_modchk_group_bin_0228 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{202, {.type = CDL_FrameCap, .obj_id = 597 /* frame_modchk_group_bin_0322 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{203, {.type = CDL_FrameCap, .obj_id = 385 /* frame_modchk_group_bin_0094 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{204, {.type = CDL_FrameCap, .obj_id = 471 /* frame_modchk_group_bin_0188 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{205, {.type = CDL_FrameCap, .obj_id = 558 /* frame_modchk_group_bin_0279 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{206, {.type = CDL_FrameCap, .obj_id = 345 /* frame_modchk_group_bin_0048 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{207, {.type = CDL_FrameCap, .obj_id = 432 /* frame_modchk_group_bin_0145 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{208, {.type = CDL_FrameCap, .obj_id = 518 /* frame_modchk_group_bin_0237 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{209, {.type = CDL_FrameCap, .obj_id = 309 /* frame_modchk_group_bin_0007 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{210, {.type = CDL_FrameCap, .obj_id = 392 /* frame_modchk_group_bin_0101 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{211, {.type = CDL_FrameCap, .obj_id = 478 /* frame_modchk_group_bin_0195 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{212, {.type = CDL_FrameCap, .obj_id = 566 /* frame_modchk_group_bin_0288 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{213, {.type = CDL_FrameCap, .obj_id = 353 /* frame_modchk_group_bin_0057 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{214, {.type = CDL_FrameCap, .obj_id = 439 /* frame_modchk_group_bin_0152 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{215, {.type = CDL_FrameCap, .obj_id = 526 /* frame_modchk_group_bin_0245 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{216, {.type = CDL_FrameCap, .obj_id = 369 /* frame_modchk_group_bin_0076 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{217, {.type = CDL_FrameCap, .obj_id = 420 /* frame_modchk_group_bin_0132 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{218, {.type = CDL_FrameCap, .obj_id = 487 /* frame_modchk_group_bin_0204 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{219, {.type = CDL_FrameCap, .obj_id = 470 /* frame_modchk_group_bin_0187 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{220, {.type = CDL_FrameCap, .obj_id = 308 /* frame_modchk_group_bin_0006 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{221, {.type = CDL_FrameCap, .obj_id = 438 /* frame_modchk_group_bin_0151 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{222, {.type = CDL_FrameCap, .obj_id = 573 /* frame_modchk_group_bin_0295 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{223, {.type = CDL_FrameCap, .obj_id = 407 /* frame_modchk_group_bin_0119 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{224, {.type = CDL_FrameCap, .obj_id = 409 /* frame_modchk_group_bin_0121 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{225, {.type = CDL_FrameCap, .obj_id = 494 /* frame_modchk_group_bin_0211 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{226, {.type = CDL_FrameCap, .obj_id = 582 /* frame_modchk_group_bin_0305 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{227, {.type = CDL_FrameCap, .obj_id = 367 /* frame_modchk_group_bin_0074 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{228, {.type = CDL_FrameCap, .obj_id = 455 /* frame_modchk_group_bin_0169 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{229, {.type = CDL_FrameCap, .obj_id = 541 /* frame_modchk_group_bin_0262 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{230, {.type = CDL_FrameCap, .obj_id = 418 /* frame_modchk_group_bin_0130 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{231, {.type = CDL_FrameCap, .obj_id = 415 /* frame_modchk_group_bin_0127 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{232, {.type = CDL_FrameCap, .obj_id = 501 /* frame_modchk_group_bin_0218 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{233, {.type = CDL_FrameCap, .obj_id = 545 /* frame_modchk_group_bin_0266 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{234, {.type = CDL_FrameCap, .obj_id = 374 /* frame_modchk_group_bin_0083 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{235, {.type = CDL_FrameCap, .obj_id = 462 /* frame_modchk_group_bin_0178 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{236, {.type = CDL_FrameCap, .obj_id = 547 /* frame_modchk_group_bin_0268 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{237, {.type = CDL_FrameCap, .obj_id = 337 /* frame_modchk_group_bin_0039 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{238, {.type = CDL_FrameCap, .obj_id = 423 /* frame_modchk_group_bin_0136 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{239, {.type = CDL_FrameCap, .obj_id = 507 /* frame_modchk_group_bin_0225 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{240, {.type = CDL_FrameCap, .obj_id = 595 /* frame_modchk_group_bin_0320 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{241, {.type = CDL_FrameCap, .obj_id = 382 /* frame_modchk_group_bin_0091 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{242, {.type = CDL_FrameCap, .obj_id = 468 /* frame_modchk_group_bin_0185 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{243, {.type = CDL_FrameCap, .obj_id = 555 /* frame_modchk_group_bin_0276 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{244, {.type = CDL_FrameCap, .obj_id = 343 /* frame_modchk_group_bin_0046 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{245, {.type = CDL_FrameCap, .obj_id = 430 /* frame_modchk_group_bin_0143 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{246, {.type = CDL_FrameCap, .obj_id = 514 /* frame_modchk_group_bin_0233 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{247, {.type = CDL_FrameCap, .obj_id = 404 /* frame_modchk_group_bin_0116 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{248, {.type = CDL_FrameCap, .obj_id = 457 /* frame_modchk_group_bin_0171 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{249, {.type = CDL_FrameCap, .obj_id = 553 /* frame_modchk_group_bin_0274 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{250, {.type = CDL_FrameCap, .obj_id = 425 /* frame_modchk_group_bin_0138 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{251, {.type = CDL_FrameCap, .obj_id = 557 /* frame_modchk_group_bin_0278 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{252, {.type = CDL_FrameCap, .obj_id = 391 /* frame_modchk_group_bin_0100 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{253, {.type = CDL_FrameCap, .obj_id = 525 /* frame_modchk_group_bin_0244 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{254, {.type = CDL_FrameCap, .obj_id = 359 /* frame_modchk_group_bin_0063 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{255, {.type = CDL_FrameCap, .obj_id = 492 /* frame_modchk_group_bin_0209 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{256, {.type = CDL_FrameCap, .obj_id = 331 /* frame_modchk_group_bin_0030 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{257, {.type = CDL_FrameCap, .obj_id = 463 /* frame_modchk_group_bin_0179 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{258, {.type = CDL_FrameCap, .obj_id = 513 /* frame_modchk_group_bin_0232 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{259, {.type = CDL_FrameCap, .obj_id = 445 /* frame_modchk_group_bin_0159 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{260, {.type = CDL_FrameCap, .obj_id = 563 /* frame_modchk_group_bin_0284 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{261, {.type = CDL_FrameCap, .obj_id = 397 /* frame_modchk_group_bin_0107 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{262, {.type = CDL_FrameCap, .obj_id = 531 /* frame_modchk_group_bin_0251 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{263, {.type = CDL_FrameCap, .obj_id = 575 /* frame_modchk_group_bin_0297 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{264, {.type = CDL_FrameCap, .obj_id = 580 /* frame_modchk_group_bin_0303 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{265, {.type = CDL_FrameCap, .obj_id = 365 /* frame_modchk_group_bin_0072 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{266, {.type = CDL_FrameCap, .obj_id = 452 /* frame_modchk_group_bin_0166 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{267, {.type = CDL_FrameCap, .obj_id = 539 /* frame_modchk_group_bin_0260 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{268, {.type = CDL_FrameCap, .obj_id = 328 /* frame_modchk_group_bin_0027 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{269, {.type = CDL_FrameCap, .obj_id = 413 /* frame_modchk_group_bin_0125 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{270, {.type = CDL_FrameCap, .obj_id = 499 /* frame_modchk_group_bin_0216 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{271, {.type = CDL_FrameCap, .obj_id = 587 /* frame_modchk_group_bin_0310 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{272, {.type = CDL_FrameCap, .obj_id = 372 /* frame_modchk_group_bin_0080 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{273, {.type = CDL_FrameCap, .obj_id = 460 /* frame_modchk_group_bin_0176 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{274, {.type = CDL_FrameCap, .obj_id = 400 /* frame_modchk_group_bin_0111 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{275, {.type = CDL_FrameCap, .obj_id = 335 /* frame_modchk_group_bin_0037 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{276, {.type = CDL_FrameCap, .obj_id = 421 /* frame_modchk_group_bin_0133 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{277, {.type = CDL_FrameCap, .obj_id = 505 /* frame_modchk_group_bin_0223 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{278, {.type = CDL_FrameCap, .obj_id = 593 /* frame_modchk_group_bin_0318 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{279, {.type = CDL_FrameCap, .obj_id = 380 /* frame_modchk_group_bin_0089 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{280, {.type = CDL_FrameCap, .obj_id = 543 /* frame_modchk_group_bin_0264 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{281, {.type = CDL_FrameCap, .obj_id = 377 /* frame_modchk_group_bin_0086 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{282, {.type = CDL_FrameCap, .obj_id = 458 /* frame_modchk_group_bin_0173 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{283, {.type = CDL_FrameCap, .obj_id = 389 /* frame_modchk_group_bin_0098 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{284, {.type = CDL_FrameCap, .obj_id = 477 /* frame_modchk_group_bin_0194 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{285, {.type = CDL_FrameCap, .obj_id = 315 /* frame_modchk_group_bin_0014 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{286, {.type = CDL_FrameCap, .obj_id = 446 /* frame_modchk_group_bin_0160 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{287, {.type = CDL_FrameCap, .obj_id = 474 /* frame_modchk_group_bin_0191 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{288, {.type = CDL_FrameCap, .obj_id = 562 /* frame_modchk_group_bin_0283 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{289, {.type = CDL_FrameCap, .obj_id = 548 /* frame_modchk_group_bin_0269 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{290, {.type = CDL_FrameCap, .obj_id = 517 /* frame_modchk_group_bin_0236 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{291, {.type = CDL_FrameCap, .obj_id = 325 /* frame_modchk_group_bin_0024 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{292, {.type = CDL_FrameCap, .obj_id = 350 /* frame_modchk_group_bin_0054 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{293, {.type = CDL_FrameCap, .obj_id = 483 /* frame_modchk_group_bin_0200 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{294, {.type = CDL_FrameCap, .obj_id = 320 /* frame_modchk_group_bin_0019 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{295, {.type = CDL_FrameCap, .obj_id = 570 /* frame_modchk_group_bin_0292 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{296, {.type = CDL_FrameCap, .obj_id = 538 /* frame_modchk_group_bin_0259 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{298, {.type = CDL_FrameCap, .obj_id = 1229 /* stack__camkes_stack_modchk_0_control_0_modchk_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{299, {.type = CDL_FrameCap, .obj_id = 1230 /* stack__camkes_stack_modchk_0_control_1_modchk_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{300, {.type = CDL_FrameCap, .obj_id = 1231 /* stack__camkes_stack_modchk_0_control_2_modchk_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{301, {.type = CDL_FrameCap, .obj_id = 1232 /* stack__camkes_stack_modchk_0_control_3_modchk_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{304, {.type = CDL_FrameCap, .obj_id = 1237 /* stack__camkes_stack_modchk_modchk_iface_0000_0_modchk_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{305, {.type = CDL_FrameCap, .obj_id = 1238 /* stack__camkes_stack_modchk_modchk_iface_0000_1_modchk_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{306, {.type = CDL_FrameCap, .obj_id = 1239 /* stack__camkes_stack_modchk_modchk_iface_0000_2_modchk_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{307, {.type = CDL_FrameCap, .obj_id = 1240 /* stack__camkes_stack_modchk_modchk_iface_0000_3_modchk_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{310, {.type = CDL_FrameCap, .obj_id = 1233 /* stack__camkes_stack_modchk_0_fault_handler_0000_0_modchk_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{311, {.type = CDL_FrameCap, .obj_id = 1234 /* stack__camkes_stack_modchk_0_fault_handler_0000_1_modchk_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{312, {.type = CDL_FrameCap, .obj_id = 1235 /* stack__camkes_stack_modchk_0_fault_handler_0000_2_modchk_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{313, {.type = CDL_FrameCap, .obj_id = 1236 /* stack__camkes_stack_modchk_0_fault_handler_0000_3_modchk_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{316, {.type = CDL_FrameCap, .obj_id = 1193 /* modchk_frame__camkes_ipc_buffer_modchk_0_control */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{319, {.type = CDL_FrameCap, .obj_id = 1195 /* modchk_frame__camkes_ipc_buffer_modchk_modchk_iface_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{322, {.type = CDL_FrameCap, .obj_id = 1194 /* modchk_frame__camkes_ipc_buffer_modchk_0_fault_handler_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},

},
},
[1211] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "pt_modtx_group_bin_0002",
#endif
.type = CDL_PT,
.slots.num = 311,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_FrameCap, .obj_id = 599 /* frame_modtx_group_bin_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{1, {.type = CDL_FrameCap, .obj_id = 600 /* frame_modtx_group_bin_0001 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{2, {.type = CDL_FrameCap, .obj_id = 769 /* frame_modtx_group_bin_0188 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{3, {.type = CDL_FrameCap, .obj_id = 845 /* frame_modtx_group_bin_0269 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{4, {.type = CDL_FrameCap, .obj_id = 626 /* frame_modtx_group_bin_0028 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{5, {.type = CDL_FrameCap, .obj_id = 703 /* frame_modtx_group_bin_0118 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{6, {.type = CDL_FrameCap, .obj_id = 778 /* frame_modtx_group_bin_0197 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{7, {.type = CDL_FrameCap, .obj_id = 855 /* frame_modtx_group_bin_0279 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{8, {.type = CDL_FrameCap, .obj_id = 635 /* frame_modtx_group_bin_0041 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{9, {.type = CDL_FrameCap, .obj_id = 711 /* frame_modtx_group_bin_0126 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{10, {.type = CDL_FrameCap, .obj_id = 788 /* frame_modtx_group_bin_0207 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{11, {.type = CDL_FrameCap, .obj_id = 865 /* frame_modtx_group_bin_0290 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{12, {.type = CDL_FrameCap, .obj_id = 643 /* frame_modtx_group_bin_0049 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{13, {.type = CDL_FrameCap, .obj_id = 721 /* frame_modtx_group_bin_0137 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{14, {.type = CDL_FrameCap, .obj_id = 797 /* frame_modtx_group_bin_0216 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{15, {.type = CDL_FrameCap, .obj_id = 875 /* frame_modtx_group_bin_0300 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{16, {.type = CDL_FrameCap, .obj_id = 653 /* frame_modtx_group_bin_0060 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{17, {.type = CDL_FrameCap, .obj_id = 730 /* frame_modtx_group_bin_0146 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{18, {.type = CDL_FrameCap, .obj_id = 805 /* frame_modtx_group_bin_0225 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{19, {.type = CDL_FrameCap, .obj_id = 884 /* frame_modtx_group_bin_0310 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{20, {.type = CDL_FrameCap, .obj_id = 661 /* frame_modtx_group_bin_0071 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{21, {.type = CDL_FrameCap, .obj_id = 739 /* frame_modtx_group_bin_0155 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{22, {.type = CDL_FrameCap, .obj_id = 816 /* frame_modtx_group_bin_0237 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{23, {.type = CDL_FrameCap, .obj_id = 892 /* frame_modtx_group_bin_0320 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{24, {.type = CDL_FrameCap, .obj_id = 670 /* frame_modtx_group_bin_0081 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{25, {.type = CDL_FrameCap, .obj_id = 675 /* frame_modtx_group_bin_0087 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{26, {.type = CDL_FrameCap, .obj_id = 826 /* frame_modtx_group_bin_0248 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{27, {.type = CDL_FrameCap, .obj_id = 825 /* frame_modtx_group_bin_0247 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{28, {.type = CDL_FrameCap, .obj_id = 603 /* frame_modtx_group_bin_0004 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{29, {.type = CDL_FrameCap, .obj_id = 758 /* frame_modtx_group_bin_0176 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{30, {.type = CDL_FrameCap, .obj_id = 834 /* frame_modtx_group_bin_0257 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{31, {.type = CDL_FrameCap, .obj_id = 615 /* frame_modtx_group_bin_0017 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{32, {.type = CDL_FrameCap, .obj_id = 690 /* frame_modtx_group_bin_0102 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{33, {.type = CDL_FrameCap, .obj_id = 766 /* frame_modtx_group_bin_0185 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{34, {.type = CDL_FrameCap, .obj_id = 842 /* frame_modtx_group_bin_0266 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{35, {.type = CDL_FrameCap, .obj_id = 624 /* frame_modtx_group_bin_0026 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{36, {.type = CDL_FrameCap, .obj_id = 700 /* frame_modtx_group_bin_0115 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{37, {.type = CDL_FrameCap, .obj_id = 776 /* frame_modtx_group_bin_0195 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{38, {.type = CDL_FrameCap, .obj_id = 852 /* frame_modtx_group_bin_0276 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{39, {.type = CDL_FrameCap, .obj_id = 633 /* frame_modtx_group_bin_0038 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{40, {.type = CDL_FrameCap, .obj_id = 709 /* frame_modtx_group_bin_0124 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{41, {.type = CDL_FrameCap, .obj_id = 786 /* frame_modtx_group_bin_0205 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{42, {.type = CDL_FrameCap, .obj_id = 863 /* frame_modtx_group_bin_0288 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{43, {.type = CDL_FrameCap, .obj_id = 641 /* frame_modtx_group_bin_0047 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{44, {.type = CDL_FrameCap, .obj_id = 719 /* frame_modtx_group_bin_0134 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{45, {.type = CDL_FrameCap, .obj_id = 795 /* frame_modtx_group_bin_0214 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{46, {.type = CDL_FrameCap, .obj_id = 873 /* frame_modtx_group_bin_0298 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{47, {.type = CDL_FrameCap, .obj_id = 651 /* frame_modtx_group_bin_0058 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{48, {.type = CDL_FrameCap, .obj_id = 728 /* frame_modtx_group_bin_0144 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{49, {.type = CDL_FrameCap, .obj_id = 803 /* frame_modtx_group_bin_0223 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{50, {.type = CDL_FrameCap, .obj_id = 882 /* frame_modtx_group_bin_0308 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{51, {.type = CDL_FrameCap, .obj_id = 659 /* frame_modtx_group_bin_0068 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{52, {.type = CDL_FrameCap, .obj_id = 737 /* frame_modtx_group_bin_0153 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{53, {.type = CDL_FrameCap, .obj_id = 812 /* frame_modtx_group_bin_0233 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{54, {.type = CDL_FrameCap, .obj_id = 890 /* frame_modtx_group_bin_0318 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{55, {.type = CDL_FrameCap, .obj_id = 668 /* frame_modtx_group_bin_0078 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{56, {.type = CDL_FrameCap, .obj_id = 746 /* frame_modtx_group_bin_0163 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{57, {.type = CDL_FrameCap, .obj_id = 824 /* frame_modtx_group_bin_0245 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{58, {.type = CDL_FrameCap, .obj_id = 750 /* frame_modtx_group_bin_0167 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{59, {.type = CDL_FrameCap, .obj_id = 678 /* frame_modtx_group_bin_0090 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{60, {.type = CDL_FrameCap, .obj_id = 756 /* frame_modtx_group_bin_0173 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{61, {.type = CDL_FrameCap, .obj_id = 832 /* frame_modtx_group_bin_0255 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{62, {.type = CDL_FrameCap, .obj_id = 613 /* frame_modtx_group_bin_0015 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{63, {.type = CDL_FrameCap, .obj_id = 687 /* frame_modtx_group_bin_0099 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{64, {.type = CDL_FrameCap, .obj_id = 764 /* frame_modtx_group_bin_0183 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{65, {.type = CDL_FrameCap, .obj_id = 840 /* frame_modtx_group_bin_0264 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{66, {.type = CDL_FrameCap, .obj_id = 621 /* frame_modtx_group_bin_0023 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{67, {.type = CDL_FrameCap, .obj_id = 698 /* frame_modtx_group_bin_0112 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{68, {.type = CDL_FrameCap, .obj_id = 773 /* frame_modtx_group_bin_0192 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{69, {.type = CDL_FrameCap, .obj_id = 850 /* frame_modtx_group_bin_0274 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{70, {.type = CDL_FrameCap, .obj_id = 631 /* frame_modtx_group_bin_0035 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{71, {.type = CDL_FrameCap, .obj_id = 707 /* frame_modtx_group_bin_0122 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{72, {.type = CDL_FrameCap, .obj_id = 783 /* frame_modtx_group_bin_0202 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{73, {.type = CDL_FrameCap, .obj_id = 860 /* frame_modtx_group_bin_0284 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{74, {.type = CDL_FrameCap, .obj_id = 639 /* frame_modtx_group_bin_0045 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{75, {.type = CDL_FrameCap, .obj_id = 716 /* frame_modtx_group_bin_0131 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{76, {.type = CDL_FrameCap, .obj_id = 792 /* frame_modtx_group_bin_0211 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{77, {.type = CDL_FrameCap, .obj_id = 870 /* frame_modtx_group_bin_0295 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{78, {.type = CDL_FrameCap, .obj_id = 648 /* frame_modtx_group_bin_0055 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{79, {.type = CDL_FrameCap, .obj_id = 726 /* frame_modtx_group_bin_0142 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{80, {.type = CDL_FrameCap, .obj_id = 801 /* frame_modtx_group_bin_0221 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{81, {.type = CDL_FrameCap, .obj_id = 879 /* frame_modtx_group_bin_0305 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{82, {.type = CDL_FrameCap, .obj_id = 657 /* frame_modtx_group_bin_0065 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{83, {.type = CDL_FrameCap, .obj_id = 734 /* frame_modtx_group_bin_0150 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{84, {.type = CDL_FrameCap, .obj_id = 809 /* frame_modtx_group_bin_0230 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{85, {.type = CDL_FrameCap, .obj_id = 888 /* frame_modtx_group_bin_0315 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{86, {.type = CDL_FrameCap, .obj_id = 665 /* frame_modtx_group_bin_0075 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{87, {.type = CDL_FrameCap, .obj_id = 744 /* frame_modtx_group_bin_0161 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{88, {.type = CDL_FrameCap, .obj_id = 821 /* frame_modtx_group_bin_0242 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{89, {.type = CDL_FrameCap, .obj_id = 601 /* frame_modtx_group_bin_0002 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{90, {.type = CDL_FrameCap, .obj_id = 676 /* frame_modtx_group_bin_0088 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{91, {.type = CDL_FrameCap, .obj_id = 753 /* frame_modtx_group_bin_0170 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{92, {.type = CDL_FrameCap, .obj_id = 831 /* frame_modtx_group_bin_0254 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{93, {.type = CDL_FrameCap, .obj_id = 611 /* frame_modtx_group_bin_0013 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{94, {.type = CDL_FrameCap, .obj_id = 685 /* frame_modtx_group_bin_0097 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{95, {.type = CDL_FrameCap, .obj_id = 763 /* frame_modtx_group_bin_0182 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{96, {.type = CDL_FrameCap, .obj_id = 838 /* frame_modtx_group_bin_0262 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{97, {.type = CDL_FrameCap, .obj_id = 620 /* frame_modtx_group_bin_0022 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{98, {.type = CDL_FrameCap, .obj_id = 695 /* frame_modtx_group_bin_0108 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{99, {.type = CDL_FrameCap, .obj_id = 772 /* frame_modtx_group_bin_0191 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{100, {.type = CDL_FrameCap, .obj_id = 847 /* frame_modtx_group_bin_0271 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{101, {.type = CDL_FrameCap, .obj_id = 629 /* frame_modtx_group_bin_0031 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{102, {.type = CDL_FrameCap, .obj_id = 705 /* frame_modtx_group_bin_0120 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{103, {.type = CDL_FrameCap, .obj_id = 781 /* frame_modtx_group_bin_0200 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{104, {.type = CDL_FrameCap, .obj_id = 857 /* frame_modtx_group_bin_0281 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{105, {.type = CDL_FrameCap, .obj_id = 637 /* frame_modtx_group_bin_0043 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{106, {.type = CDL_FrameCap, .obj_id = 713 /* frame_modtx_group_bin_0128 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{107, {.type = CDL_FrameCap, .obj_id = 790 /* frame_modtx_group_bin_0209 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{108, {.type = CDL_FrameCap, .obj_id = 868 /* frame_modtx_group_bin_0293 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{109, {.type = CDL_FrameCap, .obj_id = 645 /* frame_modtx_group_bin_0052 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{110, {.type = CDL_FrameCap, .obj_id = 724 /* frame_modtx_group_bin_0140 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{111, {.type = CDL_FrameCap, .obj_id = 799 /* frame_modtx_group_bin_0219 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{112, {.type = CDL_FrameCap, .obj_id = 877 /* frame_modtx_group_bin_0303 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{113, {.type = CDL_FrameCap, .obj_id = 655 /* frame_modtx_group_bin_0062 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{114, {.type = CDL_FrameCap, .obj_id = 732 /* frame_modtx_group_bin_0148 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{115, {.type = CDL_FrameCap, .obj_id = 807 /* frame_modtx_group_bin_0228 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{116, {.type = CDL_FrameCap, .obj_id = 886 /* frame_modtx_group_bin_0312 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{117, {.type = CDL_FrameCap, .obj_id = 663 /* frame_modtx_group_bin_0073 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{118, {.type = CDL_FrameCap, .obj_id = 741 /* frame_modtx_group_bin_0158 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{119, {.type = CDL_FrameCap, .obj_id = 818 /* frame_modtx_group_bin_0239 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{120, {.type = CDL_FrameCap, .obj_id = 894 /* frame_modtx_group_bin_0322 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{121, {.type = CDL_FrameCap, .obj_id = 672 /* frame_modtx_group_bin_0084 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{122, {.type = CDL_FrameCap, .obj_id = 751 /* frame_modtx_group_bin_0168 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{123, {.type = CDL_FrameCap, .obj_id = 829 /* frame_modtx_group_bin_0251 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{124, {.type = CDL_FrameCap, .obj_id = 609 /* frame_modtx_group_bin_0011 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{125, {.type = CDL_FrameCap, .obj_id = 683 /* frame_modtx_group_bin_0095 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{126, {.type = CDL_FrameCap, .obj_id = 761 /* frame_modtx_group_bin_0179 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{127, {.type = CDL_FrameCap, .obj_id = 836 /* frame_modtx_group_bin_0260 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{128, {.type = CDL_FrameCap, .obj_id = 618 /* frame_modtx_group_bin_0020 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{129, {.type = CDL_FrameCap, .obj_id = 692 /* frame_modtx_group_bin_0105 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{130, {.type = CDL_FrameCap, .obj_id = 646 /* frame_modtx_group_bin_0053 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{131, {.type = CDL_FrameCap, .obj_id = 733 /* frame_modtx_group_bin_0149 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{132, {.type = CDL_FrameCap, .obj_id = 819 /* frame_modtx_group_bin_0240 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{133, {.type = CDL_FrameCap, .obj_id = 610 /* frame_modtx_group_bin_0012 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{134, {.type = CDL_FrameCap, .obj_id = 693 /* frame_modtx_group_bin_0106 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{135, {.type = CDL_FrameCap, .obj_id = 779 /* frame_modtx_group_bin_0198 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{136, {.type = CDL_FrameCap, .obj_id = 867 /* frame_modtx_group_bin_0292 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{137, {.type = CDL_FrameCap, .obj_id = 654 /* frame_modtx_group_bin_0061 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{138, {.type = CDL_FrameCap, .obj_id = 740 /* frame_modtx_group_bin_0157 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{139, {.type = CDL_FrameCap, .obj_id = 827 /* frame_modtx_group_bin_0249 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{140, {.type = CDL_FrameCap, .obj_id = 616 /* frame_modtx_group_bin_0018 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{141, {.type = CDL_FrameCap, .obj_id = 702 /* frame_modtx_group_bin_0117 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{142, {.type = CDL_FrameCap, .obj_id = 787 /* frame_modtx_group_bin_0206 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{143, {.type = CDL_FrameCap, .obj_id = 874 /* frame_modtx_group_bin_0299 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{144, {.type = CDL_FrameCap, .obj_id = 660 /* frame_modtx_group_bin_0070 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{145, {.type = CDL_FrameCap, .obj_id = 747 /* frame_modtx_group_bin_0164 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{146, {.type = CDL_FrameCap, .obj_id = 833 /* frame_modtx_group_bin_0256 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{147, {.type = CDL_FrameCap, .obj_id = 623 /* frame_modtx_group_bin_0025 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{148, {.type = CDL_FrameCap, .obj_id = 708 /* frame_modtx_group_bin_0123 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{149, {.type = CDL_FrameCap, .obj_id = 794 /* frame_modtx_group_bin_0213 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{150, {.type = CDL_FrameCap, .obj_id = 881 /* frame_modtx_group_bin_0307 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{151, {.type = CDL_FrameCap, .obj_id = 667 /* frame_modtx_group_bin_0077 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{152, {.type = CDL_FrameCap, .obj_id = 793 /* frame_modtx_group_bin_0212 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{153, {.type = CDL_FrameCap, .obj_id = 748 /* frame_modtx_group_bin_0165 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{154, {.type = CDL_FrameCap, .obj_id = 762 /* frame_modtx_group_bin_0180 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{155, {.type = CDL_FrameCap, .obj_id = 607 /* frame_modtx_group_bin_0008 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{156, {.type = CDL_FrameCap, .obj_id = 680 /* frame_modtx_group_bin_0092 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{157, {.type = CDL_FrameCap, .obj_id = 861 /* frame_modtx_group_bin_0285 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{158, {.type = CDL_FrameCap, .obj_id = 696 /* frame_modtx_group_bin_0109 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{159, {.type = CDL_FrameCap, .obj_id = 830 /* frame_modtx_group_bin_0252 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{160, {.type = CDL_FrameCap, .obj_id = 848 /* frame_modtx_group_bin_0272 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{161, {.type = CDL_FrameCap, .obj_id = 638 /* frame_modtx_group_bin_0044 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{162, {.type = CDL_FrameCap, .obj_id = 725 /* frame_modtx_group_bin_0141 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{163, {.type = CDL_FrameCap, .obj_id = 808 /* frame_modtx_group_bin_0229 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{164, {.type = CDL_FrameCap, .obj_id = 602 /* frame_modtx_group_bin_0003 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{165, {.type = CDL_FrameCap, .obj_id = 684 /* frame_modtx_group_bin_0096 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{166, {.type = CDL_FrameCap, .obj_id = 770 /* frame_modtx_group_bin_0189 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{167, {.type = CDL_FrameCap, .obj_id = 856 /* frame_modtx_group_bin_0280 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{168, {.type = CDL_FrameCap, .obj_id = 644 /* frame_modtx_group_bin_0051 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{169, {.type = CDL_FrameCap, .obj_id = 731 /* frame_modtx_group_bin_0147 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{170, {.type = CDL_FrameCap, .obj_id = 817 /* frame_modtx_group_bin_0238 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{171, {.type = CDL_FrameCap, .obj_id = 608 /* frame_modtx_group_bin_0010 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{172, {.type = CDL_FrameCap, .obj_id = 691 /* frame_modtx_group_bin_0104 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{173, {.type = CDL_FrameCap, .obj_id = 777 /* frame_modtx_group_bin_0196 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{174, {.type = CDL_FrameCap, .obj_id = 864 /* frame_modtx_group_bin_0289 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{175, {.type = CDL_FrameCap, .obj_id = 652 /* frame_modtx_group_bin_0059 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{176, {.type = CDL_FrameCap, .obj_id = 738 /* frame_modtx_group_bin_0154 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{177, {.type = CDL_FrameCap, .obj_id = 627 /* frame_modtx_group_bin_0029 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{178, {.type = CDL_FrameCap, .obj_id = 614 /* frame_modtx_group_bin_0016 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{179, {.type = CDL_FrameCap, .obj_id = 699 /* frame_modtx_group_bin_0114 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{180, {.type = CDL_FrameCap, .obj_id = 785 /* frame_modtx_group_bin_0204 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{181, {.type = CDL_FrameCap, .obj_id = 872 /* frame_modtx_group_bin_0297 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{182, {.type = CDL_FrameCap, .obj_id = 658 /* frame_modtx_group_bin_0067 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{183, {.type = CDL_FrameCap, .obj_id = 745 /* frame_modtx_group_bin_0162 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{184, {.type = CDL_FrameCap, .obj_id = 880 /* frame_modtx_group_bin_0306 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{185, {.type = CDL_FrameCap, .obj_id = 714 /* frame_modtx_group_bin_0129 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{186, {.type = CDL_FrameCap, .obj_id = 604 /* frame_modtx_group_bin_0005 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{187, {.type = CDL_FrameCap, .obj_id = 681 /* frame_modtx_group_bin_0093 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{188, {.type = CDL_FrameCap, .obj_id = 813 /* frame_modtx_group_bin_0234 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{189, {.type = CDL_FrameCap, .obj_id = 649 /* frame_modtx_group_bin_0056 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{190, {.type = CDL_FrameCap, .obj_id = 782 /* frame_modtx_group_bin_0201 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{191, {.type = CDL_FrameCap, .obj_id = 619 /* frame_modtx_group_bin_0021 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{192, {.type = CDL_FrameCap, .obj_id = 630 /* frame_modtx_group_bin_0032 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{193, {.type = CDL_FrameCap, .obj_id = 885 /* frame_modtx_group_bin_0311 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{194, {.type = CDL_FrameCap, .obj_id = 800 /* frame_modtx_group_bin_0220 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{195, {.type = CDL_FrameCap, .obj_id = 887 /* frame_modtx_group_bin_0313 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{196, {.type = CDL_FrameCap, .obj_id = 673 /* frame_modtx_group_bin_0085 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{197, {.type = CDL_FrameCap, .obj_id = 820 /* frame_modtx_group_bin_0241 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{198, {.type = CDL_FrameCap, .obj_id = 846 /* frame_modtx_group_bin_0270 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{199, {.type = CDL_FrameCap, .obj_id = 636 /* frame_modtx_group_bin_0042 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{200, {.type = CDL_FrameCap, .obj_id = 723 /* frame_modtx_group_bin_0139 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{201, {.type = CDL_FrameCap, .obj_id = 806 /* frame_modtx_group_bin_0227 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{202, {.type = CDL_FrameCap, .obj_id = 893 /* frame_modtx_group_bin_0321 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{203, {.type = CDL_FrameCap, .obj_id = 682 /* frame_modtx_group_bin_0094 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{204, {.type = CDL_FrameCap, .obj_id = 768 /* frame_modtx_group_bin_0187 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{205, {.type = CDL_FrameCap, .obj_id = 854 /* frame_modtx_group_bin_0278 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{206, {.type = CDL_FrameCap, .obj_id = 642 /* frame_modtx_group_bin_0048 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{207, {.type = CDL_FrameCap, .obj_id = 729 /* frame_modtx_group_bin_0145 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{208, {.type = CDL_FrameCap, .obj_id = 815 /* frame_modtx_group_bin_0236 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{209, {.type = CDL_FrameCap, .obj_id = 606 /* frame_modtx_group_bin_0007 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{210, {.type = CDL_FrameCap, .obj_id = 689 /* frame_modtx_group_bin_0101 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{211, {.type = CDL_FrameCap, .obj_id = 775 /* frame_modtx_group_bin_0194 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{212, {.type = CDL_FrameCap, .obj_id = 862 /* frame_modtx_group_bin_0287 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{213, {.type = CDL_FrameCap, .obj_id = 650 /* frame_modtx_group_bin_0057 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{214, {.type = CDL_FrameCap, .obj_id = 736 /* frame_modtx_group_bin_0152 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{215, {.type = CDL_FrameCap, .obj_id = 823 /* frame_modtx_group_bin_0244 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{216, {.type = CDL_FrameCap, .obj_id = 666 /* frame_modtx_group_bin_0076 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{217, {.type = CDL_FrameCap, .obj_id = 717 /* frame_modtx_group_bin_0132 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{218, {.type = CDL_FrameCap, .obj_id = 784 /* frame_modtx_group_bin_0203 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{219, {.type = CDL_FrameCap, .obj_id = 767 /* frame_modtx_group_bin_0186 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{220, {.type = CDL_FrameCap, .obj_id = 605 /* frame_modtx_group_bin_0006 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{221, {.type = CDL_FrameCap, .obj_id = 735 /* frame_modtx_group_bin_0151 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{222, {.type = CDL_FrameCap, .obj_id = 869 /* frame_modtx_group_bin_0294 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{223, {.type = CDL_FrameCap, .obj_id = 704 /* frame_modtx_group_bin_0119 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{224, {.type = CDL_FrameCap, .obj_id = 706 /* frame_modtx_group_bin_0121 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{225, {.type = CDL_FrameCap, .obj_id = 791 /* frame_modtx_group_bin_0210 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{226, {.type = CDL_FrameCap, .obj_id = 878 /* frame_modtx_group_bin_0304 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{227, {.type = CDL_FrameCap, .obj_id = 664 /* frame_modtx_group_bin_0074 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{228, {.type = CDL_FrameCap, .obj_id = 752 /* frame_modtx_group_bin_0169 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{229, {.type = CDL_FrameCap, .obj_id = 837 /* frame_modtx_group_bin_0261 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{230, {.type = CDL_FrameCap, .obj_id = 715 /* frame_modtx_group_bin_0130 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{231, {.type = CDL_FrameCap, .obj_id = 712 /* frame_modtx_group_bin_0127 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{232, {.type = CDL_FrameCap, .obj_id = 798 /* frame_modtx_group_bin_0217 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{233, {.type = CDL_FrameCap, .obj_id = 841 /* frame_modtx_group_bin_0265 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{234, {.type = CDL_FrameCap, .obj_id = 671 /* frame_modtx_group_bin_0083 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{235, {.type = CDL_FrameCap, .obj_id = 759 /* frame_modtx_group_bin_0177 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{236, {.type = CDL_FrameCap, .obj_id = 843 /* frame_modtx_group_bin_0267 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{237, {.type = CDL_FrameCap, .obj_id = 634 /* frame_modtx_group_bin_0039 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{238, {.type = CDL_FrameCap, .obj_id = 720 /* frame_modtx_group_bin_0136 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{239, {.type = CDL_FrameCap, .obj_id = 804 /* frame_modtx_group_bin_0224 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{240, {.type = CDL_FrameCap, .obj_id = 891 /* frame_modtx_group_bin_0319 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{241, {.type = CDL_FrameCap, .obj_id = 679 /* frame_modtx_group_bin_0091 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{242, {.type = CDL_FrameCap, .obj_id = 765 /* frame_modtx_group_bin_0184 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{243, {.type = CDL_FrameCap, .obj_id = 851 /* frame_modtx_group_bin_0275 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{244, {.type = CDL_FrameCap, .obj_id = 640 /* frame_modtx_group_bin_0046 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{245, {.type = CDL_FrameCap, .obj_id = 727 /* frame_modtx_group_bin_0143 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{246, {.type = CDL_FrameCap, .obj_id = 811 /* frame_modtx_group_bin_0232 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{247, {.type = CDL_FrameCap, .obj_id = 701 /* frame_modtx_group_bin_0116 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{248, {.type = CDL_FrameCap, .obj_id = 754 /* frame_modtx_group_bin_0171 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{249, {.type = CDL_FrameCap, .obj_id = 849 /* frame_modtx_group_bin_0273 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{250, {.type = CDL_FrameCap, .obj_id = 722 /* frame_modtx_group_bin_0138 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{251, {.type = CDL_FrameCap, .obj_id = 853 /* frame_modtx_group_bin_0277 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{252, {.type = CDL_FrameCap, .obj_id = 688 /* frame_modtx_group_bin_0100 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{253, {.type = CDL_FrameCap, .obj_id = 822 /* frame_modtx_group_bin_0243 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{254, {.type = CDL_FrameCap, .obj_id = 656 /* frame_modtx_group_bin_0063 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{255, {.type = CDL_FrameCap, .obj_id = 789 /* frame_modtx_group_bin_0208 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{256, {.type = CDL_FrameCap, .obj_id = 628 /* frame_modtx_group_bin_0030 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{257, {.type = CDL_FrameCap, .obj_id = 760 /* frame_modtx_group_bin_0178 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{258, {.type = CDL_FrameCap, .obj_id = 810 /* frame_modtx_group_bin_0231 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{259, {.type = CDL_FrameCap, .obj_id = 742 /* frame_modtx_group_bin_0159 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{260, {.type = CDL_FrameCap, .obj_id = 859 /* frame_modtx_group_bin_0283 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{261, {.type = CDL_FrameCap, .obj_id = 694 /* frame_modtx_group_bin_0107 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{262, {.type = CDL_FrameCap, .obj_id = 828 /* frame_modtx_group_bin_0250 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{263, {.type = CDL_FrameCap, .obj_id = 871 /* frame_modtx_group_bin_0296 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{264, {.type = CDL_FrameCap, .obj_id = 876 /* frame_modtx_group_bin_0302 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{265, {.type = CDL_FrameCap, .obj_id = 662 /* frame_modtx_group_bin_0072 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{266, {.type = CDL_FrameCap, .obj_id = 749 /* frame_modtx_group_bin_0166 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{267, {.type = CDL_FrameCap, .obj_id = 835 /* frame_modtx_group_bin_0259 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{268, {.type = CDL_FrameCap, .obj_id = 625 /* frame_modtx_group_bin_0027 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{269, {.type = CDL_FrameCap, .obj_id = 710 /* frame_modtx_group_bin_0125 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{270, {.type = CDL_FrameCap, .obj_id = 796 /* frame_modtx_group_bin_0215 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{271, {.type = CDL_FrameCap, .obj_id = 883 /* frame_modtx_group_bin_0309 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{272, {.type = CDL_FrameCap, .obj_id = 669 /* frame_modtx_group_bin_0080 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{273, {.type = CDL_FrameCap, .obj_id = 757 /* frame_modtx_group_bin_0175 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{274, {.type = CDL_FrameCap, .obj_id = 697 /* frame_modtx_group_bin_0111 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{275, {.type = CDL_FrameCap, .obj_id = 632 /* frame_modtx_group_bin_0037 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{276, {.type = CDL_FrameCap, .obj_id = 718 /* frame_modtx_group_bin_0133 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{277, {.type = CDL_FrameCap, .obj_id = 802 /* frame_modtx_group_bin_0222 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{278, {.type = CDL_FrameCap, .obj_id = 889 /* frame_modtx_group_bin_0317 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{279, {.type = CDL_FrameCap, .obj_id = 677 /* frame_modtx_group_bin_0089 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{280, {.type = CDL_FrameCap, .obj_id = 839 /* frame_modtx_group_bin_0263 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{281, {.type = CDL_FrameCap, .obj_id = 674 /* frame_modtx_group_bin_0086 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{282, {.type = CDL_FrameCap, .obj_id = 755 /* frame_modtx_group_bin_0172 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{283, {.type = CDL_FrameCap, .obj_id = 686 /* frame_modtx_group_bin_0098 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{284, {.type = CDL_FrameCap, .obj_id = 774 /* frame_modtx_group_bin_0193 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{285, {.type = CDL_FrameCap, .obj_id = 612 /* frame_modtx_group_bin_0014 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{286, {.type = CDL_FrameCap, .obj_id = 743 /* frame_modtx_group_bin_0160 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{287, {.type = CDL_FrameCap, .obj_id = 771 /* frame_modtx_group_bin_0190 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{288, {.type = CDL_FrameCap, .obj_id = 858 /* frame_modtx_group_bin_0282 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{289, {.type = CDL_FrameCap, .obj_id = 844 /* frame_modtx_group_bin_0268 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{290, {.type = CDL_FrameCap, .obj_id = 814 /* frame_modtx_group_bin_0235 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{291, {.type = CDL_FrameCap, .obj_id = 622 /* frame_modtx_group_bin_0024 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{292, {.type = CDL_FrameCap, .obj_id = 647 /* frame_modtx_group_bin_0054 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{293, {.type = CDL_FrameCap, .obj_id = 780 /* frame_modtx_group_bin_0199 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{294, {.type = CDL_FrameCap, .obj_id = 617 /* frame_modtx_group_bin_0019 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{295, {.type = CDL_FrameCap, .obj_id = 866 /* frame_modtx_group_bin_0291 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{297, {.type = CDL_FrameCap, .obj_id = 1241 /* stack__camkes_stack_modtx_0_control_0_modtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{298, {.type = CDL_FrameCap, .obj_id = 1242 /* stack__camkes_stack_modtx_0_control_1_modtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{299, {.type = CDL_FrameCap, .obj_id = 1243 /* stack__camkes_stack_modtx_0_control_2_modtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{300, {.type = CDL_FrameCap, .obj_id = 1244 /* stack__camkes_stack_modtx_0_control_3_modtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{303, {.type = CDL_FrameCap, .obj_id = 1249 /* stack__camkes_stack_modtx_modtx_iface_0000_0_modtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{304, {.type = CDL_FrameCap, .obj_id = 1250 /* stack__camkes_stack_modtx_modtx_iface_0000_1_modtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{305, {.type = CDL_FrameCap, .obj_id = 1251 /* stack__camkes_stack_modtx_modtx_iface_0000_2_modtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{306, {.type = CDL_FrameCap, .obj_id = 1252 /* stack__camkes_stack_modtx_modtx_iface_0000_3_modtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{309, {.type = CDL_FrameCap, .obj_id = 1245 /* stack__camkes_stack_modtx_0_fault_handler_0000_0_modtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{310, {.type = CDL_FrameCap, .obj_id = 1246 /* stack__camkes_stack_modtx_0_fault_handler_0000_1_modtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{311, {.type = CDL_FrameCap, .obj_id = 1247 /* stack__camkes_stack_modtx_0_fault_handler_0000_2_modtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{312, {.type = CDL_FrameCap, .obj_id = 1248 /* stack__camkes_stack_modtx_0_fault_handler_0000_3_modtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{315, {.type = CDL_FrameCap, .obj_id = 1197 /* modtx_frame__camkes_ipc_buffer_modtx_0_control */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{318, {.type = CDL_FrameCap, .obj_id = 1199 /* modtx_frame__camkes_ipc_buffer_modtx_modtx_iface_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{321, {.type = CDL_FrameCap, .obj_id = 1198 /* modtx_frame__camkes_ipc_buffer_modtx_0_fault_handler_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},

},
},
[1212] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "pt_signtx_group_bin_0002",
#endif
.type = CDL_PT,
.slots.num = 313,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_FrameCap, .obj_id = 895 /* frame_signtx_group_bin_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{1, {.type = CDL_FrameCap, .obj_id = 896 /* frame_signtx_group_bin_0001 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{2, {.type = CDL_FrameCap, .obj_id = 1066 /* frame_signtx_group_bin_0190 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{3, {.type = CDL_FrameCap, .obj_id = 1143 /* frame_signtx_group_bin_0271 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{4, {.type = CDL_FrameCap, .obj_id = 923 /* frame_signtx_group_bin_0028 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{5, {.type = CDL_FrameCap, .obj_id = 1000 /* frame_signtx_group_bin_0118 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{6, {.type = CDL_FrameCap, .obj_id = 1075 /* frame_signtx_group_bin_0199 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{7, {.type = CDL_FrameCap, .obj_id = 1153 /* frame_signtx_group_bin_0281 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{8, {.type = CDL_FrameCap, .obj_id = 932 /* frame_signtx_group_bin_0041 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{9, {.type = CDL_FrameCap, .obj_id = 1008 /* frame_signtx_group_bin_0126 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{10, {.type = CDL_FrameCap, .obj_id = 1085 /* frame_signtx_group_bin_0209 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{11, {.type = CDL_FrameCap, .obj_id = 1163 /* frame_signtx_group_bin_0292 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{12, {.type = CDL_FrameCap, .obj_id = 940 /* frame_signtx_group_bin_0049 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{13, {.type = CDL_FrameCap, .obj_id = 1018 /* frame_signtx_group_bin_0137 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{14, {.type = CDL_FrameCap, .obj_id = 1094 /* frame_signtx_group_bin_0218 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{15, {.type = CDL_FrameCap, .obj_id = 1173 /* frame_signtx_group_bin_0302 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{16, {.type = CDL_FrameCap, .obj_id = 950 /* frame_signtx_group_bin_0060 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{17, {.type = CDL_FrameCap, .obj_id = 1027 /* frame_signtx_group_bin_0146 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{18, {.type = CDL_FrameCap, .obj_id = 1102 /* frame_signtx_group_bin_0227 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{19, {.type = CDL_FrameCap, .obj_id = 1182 /* frame_signtx_group_bin_0312 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{20, {.type = CDL_FrameCap, .obj_id = 958 /* frame_signtx_group_bin_0071 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{21, {.type = CDL_FrameCap, .obj_id = 1036 /* frame_signtx_group_bin_0156 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{22, {.type = CDL_FrameCap, .obj_id = 1113 /* frame_signtx_group_bin_0239 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{23, {.type = CDL_FrameCap, .obj_id = 1190 /* frame_signtx_group_bin_0322 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{24, {.type = CDL_FrameCap, .obj_id = 967 /* frame_signtx_group_bin_0081 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{25, {.type = CDL_FrameCap, .obj_id = 972 /* frame_signtx_group_bin_0087 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{26, {.type = CDL_FrameCap, .obj_id = 1123 /* frame_signtx_group_bin_0250 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{27, {.type = CDL_FrameCap, .obj_id = 1122 /* frame_signtx_group_bin_0249 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{28, {.type = CDL_FrameCap, .obj_id = 899 /* frame_signtx_group_bin_0004 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{29, {.type = CDL_FrameCap, .obj_id = 1055 /* frame_signtx_group_bin_0178 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{30, {.type = CDL_FrameCap, .obj_id = 1131 /* frame_signtx_group_bin_0259 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{31, {.type = CDL_FrameCap, .obj_id = 912 /* frame_signtx_group_bin_0017 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{32, {.type = CDL_FrameCap, .obj_id = 987 /* frame_signtx_group_bin_0102 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{33, {.type = CDL_FrameCap, .obj_id = 1063 /* frame_signtx_group_bin_0187 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{34, {.type = CDL_FrameCap, .obj_id = 1140 /* frame_signtx_group_bin_0268 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{35, {.type = CDL_FrameCap, .obj_id = 921 /* frame_signtx_group_bin_0026 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{36, {.type = CDL_FrameCap, .obj_id = 997 /* frame_signtx_group_bin_0115 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{37, {.type = CDL_FrameCap, .obj_id = 1073 /* frame_signtx_group_bin_0197 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanGrant), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{38, {.type = CDL_FrameCap, .obj_id = 1150 /* frame_signtx_group_bin_0278 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{39, {.type = CDL_FrameCap, .obj_id = 930 /* frame_signtx_group_bin_0038 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{40, {.type = CDL_FrameCap, .obj_id = 1006 /* frame_signtx_group_bin_0124 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{41, {.type = CDL_FrameCap, .obj_id = 1083 /* frame_signtx_group_bin_0207 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{42, {.type = CDL_FrameCap, .obj_id = 1161 /* frame_signtx_group_bin_0290 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{43, {.type = CDL_FrameCap, .obj_id = 938 /* frame_signtx_group_bin_0047 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{44, {.type = CDL_FrameCap, .obj_id = 1016 /* frame_signtx_group_bin_0134 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{45, {.type = CDL_FrameCap, .obj_id = 1092 /* frame_signtx_group_bin_0216 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{46, {.type = CDL_FrameCap, .obj_id = 1171 /* frame_signtx_group_bin_0300 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{47, {.type = CDL_FrameCap, .obj_id = 948 /* frame_signtx_group_bin_0058 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{48, {.type = CDL_FrameCap, .obj_id = 1025 /* frame_signtx_group_bin_0144 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{49, {.type = CDL_FrameCap, .obj_id = 1100 /* frame_signtx_group_bin_0225 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{50, {.type = CDL_FrameCap, .obj_id = 1180 /* frame_signtx_group_bin_0310 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{51, {.type = CDL_FrameCap, .obj_id = 956 /* frame_signtx_group_bin_0068 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{52, {.type = CDL_FrameCap, .obj_id = 1034 /* frame_signtx_group_bin_0154 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{53, {.type = CDL_FrameCap, .obj_id = 1109 /* frame_signtx_group_bin_0235 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{54, {.type = CDL_FrameCap, .obj_id = 1188 /* frame_signtx_group_bin_0320 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{55, {.type = CDL_FrameCap, .obj_id = 965 /* frame_signtx_group_bin_0078 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{56, {.type = CDL_FrameCap, .obj_id = 1043 /* frame_signtx_group_bin_0164 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{57, {.type = CDL_FrameCap, .obj_id = 1121 /* frame_signtx_group_bin_0247 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{58, {.type = CDL_FrameCap, .obj_id = 1047 /* frame_signtx_group_bin_0168 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{59, {.type = CDL_FrameCap, .obj_id = 975 /* frame_signtx_group_bin_0090 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{60, {.type = CDL_FrameCap, .obj_id = 1053 /* frame_signtx_group_bin_0175 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{61, {.type = CDL_FrameCap, .obj_id = 1129 /* frame_signtx_group_bin_0257 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{62, {.type = CDL_FrameCap, .obj_id = 910 /* frame_signtx_group_bin_0015 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{63, {.type = CDL_FrameCap, .obj_id = 984 /* frame_signtx_group_bin_0099 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{64, {.type = CDL_FrameCap, .obj_id = 1061 /* frame_signtx_group_bin_0185 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{65, {.type = CDL_FrameCap, .obj_id = 1138 /* frame_signtx_group_bin_0266 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{66, {.type = CDL_FrameCap, .obj_id = 918 /* frame_signtx_group_bin_0023 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{67, {.type = CDL_FrameCap, .obj_id = 995 /* frame_signtx_group_bin_0112 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{68, {.type = CDL_FrameCap, .obj_id = 1070 /* frame_signtx_group_bin_0194 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{69, {.type = CDL_FrameCap, .obj_id = 1148 /* frame_signtx_group_bin_0276 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{70, {.type = CDL_FrameCap, .obj_id = 928 /* frame_signtx_group_bin_0035 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{71, {.type = CDL_FrameCap, .obj_id = 1004 /* frame_signtx_group_bin_0122 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{72, {.type = CDL_FrameCap, .obj_id = 1080 /* frame_signtx_group_bin_0204 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{73, {.type = CDL_FrameCap, .obj_id = 1158 /* frame_signtx_group_bin_0286 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{74, {.type = CDL_FrameCap, .obj_id = 936 /* frame_signtx_group_bin_0045 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{75, {.type = CDL_FrameCap, .obj_id = 1013 /* frame_signtx_group_bin_0131 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{76, {.type = CDL_FrameCap, .obj_id = 1089 /* frame_signtx_group_bin_0213 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{77, {.type = CDL_FrameCap, .obj_id = 1168 /* frame_signtx_group_bin_0297 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{78, {.type = CDL_FrameCap, .obj_id = 945 /* frame_signtx_group_bin_0055 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{79, {.type = CDL_FrameCap, .obj_id = 1023 /* frame_signtx_group_bin_0142 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{80, {.type = CDL_FrameCap, .obj_id = 1098 /* frame_signtx_group_bin_0223 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{81, {.type = CDL_FrameCap, .obj_id = 1177 /* frame_signtx_group_bin_0307 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{82, {.type = CDL_FrameCap, .obj_id = 954 /* frame_signtx_group_bin_0065 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{83, {.type = CDL_FrameCap, .obj_id = 1031 /* frame_signtx_group_bin_0151 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{84, {.type = CDL_FrameCap, .obj_id = 1106 /* frame_signtx_group_bin_0232 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{85, {.type = CDL_FrameCap, .obj_id = 1186 /* frame_signtx_group_bin_0317 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{86, {.type = CDL_FrameCap, .obj_id = 962 /* frame_signtx_group_bin_0075 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{87, {.type = CDL_FrameCap, .obj_id = 1041 /* frame_signtx_group_bin_0162 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{88, {.type = CDL_FrameCap, .obj_id = 1118 /* frame_signtx_group_bin_0244 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{89, {.type = CDL_FrameCap, .obj_id = 897 /* frame_signtx_group_bin_0002 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{90, {.type = CDL_FrameCap, .obj_id = 973 /* frame_signtx_group_bin_0088 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{91, {.type = CDL_FrameCap, .obj_id = 1050 /* frame_signtx_group_bin_0171 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{92, {.type = CDL_FrameCap, .obj_id = 1128 /* frame_signtx_group_bin_0256 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{93, {.type = CDL_FrameCap, .obj_id = 908 /* frame_signtx_group_bin_0013 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{94, {.type = CDL_FrameCap, .obj_id = 982 /* frame_signtx_group_bin_0097 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{95, {.type = CDL_FrameCap, .obj_id = 1060 /* frame_signtx_group_bin_0184 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{96, {.type = CDL_FrameCap, .obj_id = 1136 /* frame_signtx_group_bin_0264 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{97, {.type = CDL_FrameCap, .obj_id = 917 /* frame_signtx_group_bin_0022 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{98, {.type = CDL_FrameCap, .obj_id = 992 /* frame_signtx_group_bin_0108 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{99, {.type = CDL_FrameCap, .obj_id = 1069 /* frame_signtx_group_bin_0193 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{100, {.type = CDL_FrameCap, .obj_id = 1145 /* frame_signtx_group_bin_0273 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{101, {.type = CDL_FrameCap, .obj_id = 926 /* frame_signtx_group_bin_0031 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{102, {.type = CDL_FrameCap, .obj_id = 1002 /* frame_signtx_group_bin_0120 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{103, {.type = CDL_FrameCap, .obj_id = 1078 /* frame_signtx_group_bin_0202 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{104, {.type = CDL_FrameCap, .obj_id = 1155 /* frame_signtx_group_bin_0283 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{105, {.type = CDL_FrameCap, .obj_id = 934 /* frame_signtx_group_bin_0043 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{106, {.type = CDL_FrameCap, .obj_id = 1010 /* frame_signtx_group_bin_0128 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{107, {.type = CDL_FrameCap, .obj_id = 1087 /* frame_signtx_group_bin_0211 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{108, {.type = CDL_FrameCap, .obj_id = 1166 /* frame_signtx_group_bin_0295 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{109, {.type = CDL_FrameCap, .obj_id = 942 /* frame_signtx_group_bin_0052 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{110, {.type = CDL_FrameCap, .obj_id = 1021 /* frame_signtx_group_bin_0140 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{111, {.type = CDL_FrameCap, .obj_id = 1096 /* frame_signtx_group_bin_0221 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{112, {.type = CDL_FrameCap, .obj_id = 1175 /* frame_signtx_group_bin_0305 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{113, {.type = CDL_FrameCap, .obj_id = 952 /* frame_signtx_group_bin_0062 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{114, {.type = CDL_FrameCap, .obj_id = 1029 /* frame_signtx_group_bin_0148 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{115, {.type = CDL_FrameCap, .obj_id = 1104 /* frame_signtx_group_bin_0230 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{116, {.type = CDL_FrameCap, .obj_id = 1184 /* frame_signtx_group_bin_0314 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{117, {.type = CDL_FrameCap, .obj_id = 960 /* frame_signtx_group_bin_0073 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{118, {.type = CDL_FrameCap, .obj_id = 1038 /* frame_signtx_group_bin_0159 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{119, {.type = CDL_FrameCap, .obj_id = 1115 /* frame_signtx_group_bin_0241 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{120, {.type = CDL_FrameCap, .obj_id = 1192 /* frame_signtx_group_bin_0324 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{121, {.type = CDL_FrameCap, .obj_id = 969 /* frame_signtx_group_bin_0084 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{122, {.type = CDL_FrameCap, .obj_id = 1048 /* frame_signtx_group_bin_0169 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{123, {.type = CDL_FrameCap, .obj_id = 1126 /* frame_signtx_group_bin_0253 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{124, {.type = CDL_FrameCap, .obj_id = 906 /* frame_signtx_group_bin_0011 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{125, {.type = CDL_FrameCap, .obj_id = 980 /* frame_signtx_group_bin_0095 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{126, {.type = CDL_FrameCap, .obj_id = 1058 /* frame_signtx_group_bin_0181 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{127, {.type = CDL_FrameCap, .obj_id = 1134 /* frame_signtx_group_bin_0262 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{128, {.type = CDL_FrameCap, .obj_id = 915 /* frame_signtx_group_bin_0020 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{129, {.type = CDL_FrameCap, .obj_id = 989 /* frame_signtx_group_bin_0105 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{130, {.type = CDL_FrameCap, .obj_id = 943 /* frame_signtx_group_bin_0053 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{131, {.type = CDL_FrameCap, .obj_id = 1030 /* frame_signtx_group_bin_0149 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{132, {.type = CDL_FrameCap, .obj_id = 1116 /* frame_signtx_group_bin_0242 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{133, {.type = CDL_FrameCap, .obj_id = 907 /* frame_signtx_group_bin_0012 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{134, {.type = CDL_FrameCap, .obj_id = 990 /* frame_signtx_group_bin_0106 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{135, {.type = CDL_FrameCap, .obj_id = 1076 /* frame_signtx_group_bin_0200 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{136, {.type = CDL_FrameCap, .obj_id = 1165 /* frame_signtx_group_bin_0294 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{137, {.type = CDL_FrameCap, .obj_id = 951 /* frame_signtx_group_bin_0061 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{138, {.type = CDL_FrameCap, .obj_id = 1037 /* frame_signtx_group_bin_0158 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{139, {.type = CDL_FrameCap, .obj_id = 1124 /* frame_signtx_group_bin_0251 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{140, {.type = CDL_FrameCap, .obj_id = 913 /* frame_signtx_group_bin_0018 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{141, {.type = CDL_FrameCap, .obj_id = 999 /* frame_signtx_group_bin_0117 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{142, {.type = CDL_FrameCap, .obj_id = 1084 /* frame_signtx_group_bin_0208 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{143, {.type = CDL_FrameCap, .obj_id = 1172 /* frame_signtx_group_bin_0301 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{144, {.type = CDL_FrameCap, .obj_id = 957 /* frame_signtx_group_bin_0070 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{145, {.type = CDL_FrameCap, .obj_id = 1044 /* frame_signtx_group_bin_0165 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{146, {.type = CDL_FrameCap, .obj_id = 1130 /* frame_signtx_group_bin_0258 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{147, {.type = CDL_FrameCap, .obj_id = 920 /* frame_signtx_group_bin_0025 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{148, {.type = CDL_FrameCap, .obj_id = 1005 /* frame_signtx_group_bin_0123 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{149, {.type = CDL_FrameCap, .obj_id = 1091 /* frame_signtx_group_bin_0215 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{150, {.type = CDL_FrameCap, .obj_id = 1179 /* frame_signtx_group_bin_0309 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{151, {.type = CDL_FrameCap, .obj_id = 964 /* frame_signtx_group_bin_0077 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{152, {.type = CDL_FrameCap, .obj_id = 1090 /* frame_signtx_group_bin_0214 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{153, {.type = CDL_FrameCap, .obj_id = 1045 /* frame_signtx_group_bin_0166 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{154, {.type = CDL_FrameCap, .obj_id = 1059 /* frame_signtx_group_bin_0182 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{155, {.type = CDL_FrameCap, .obj_id = 903 /* frame_signtx_group_bin_0008 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{156, {.type = CDL_FrameCap, .obj_id = 977 /* frame_signtx_group_bin_0092 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{157, {.type = CDL_FrameCap, .obj_id = 1159 /* frame_signtx_group_bin_0287 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{158, {.type = CDL_FrameCap, .obj_id = 993 /* frame_signtx_group_bin_0109 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{159, {.type = CDL_FrameCap, .obj_id = 1127 /* frame_signtx_group_bin_0254 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{160, {.type = CDL_FrameCap, .obj_id = 1146 /* frame_signtx_group_bin_0274 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{161, {.type = CDL_FrameCap, .obj_id = 935 /* frame_signtx_group_bin_0044 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{162, {.type = CDL_FrameCap, .obj_id = 1022 /* frame_signtx_group_bin_0141 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{163, {.type = CDL_FrameCap, .obj_id = 1105 /* frame_signtx_group_bin_0231 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{164, {.type = CDL_FrameCap, .obj_id = 898 /* frame_signtx_group_bin_0003 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{165, {.type = CDL_FrameCap, .obj_id = 981 /* frame_signtx_group_bin_0096 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{166, {.type = CDL_FrameCap, .obj_id = 1067 /* frame_signtx_group_bin_0191 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{167, {.type = CDL_FrameCap, .obj_id = 1154 /* frame_signtx_group_bin_0282 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{168, {.type = CDL_FrameCap, .obj_id = 941 /* frame_signtx_group_bin_0051 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{169, {.type = CDL_FrameCap, .obj_id = 1028 /* frame_signtx_group_bin_0147 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{170, {.type = CDL_FrameCap, .obj_id = 1114 /* frame_signtx_group_bin_0240 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{171, {.type = CDL_FrameCap, .obj_id = 905 /* frame_signtx_group_bin_0010 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{172, {.type = CDL_FrameCap, .obj_id = 988 /* frame_signtx_group_bin_0104 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{173, {.type = CDL_FrameCap, .obj_id = 1074 /* frame_signtx_group_bin_0198 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{174, {.type = CDL_FrameCap, .obj_id = 1162 /* frame_signtx_group_bin_0291 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{175, {.type = CDL_FrameCap, .obj_id = 949 /* frame_signtx_group_bin_0059 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{176, {.type = CDL_FrameCap, .obj_id = 1035 /* frame_signtx_group_bin_0155 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{177, {.type = CDL_FrameCap, .obj_id = 924 /* frame_signtx_group_bin_0029 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{178, {.type = CDL_FrameCap, .obj_id = 911 /* frame_signtx_group_bin_0016 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{179, {.type = CDL_FrameCap, .obj_id = 996 /* frame_signtx_group_bin_0114 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{180, {.type = CDL_FrameCap, .obj_id = 1082 /* frame_signtx_group_bin_0206 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{181, {.type = CDL_FrameCap, .obj_id = 1170 /* frame_signtx_group_bin_0299 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{182, {.type = CDL_FrameCap, .obj_id = 955 /* frame_signtx_group_bin_0067 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{183, {.type = CDL_FrameCap, .obj_id = 1042 /* frame_signtx_group_bin_0163 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{184, {.type = CDL_FrameCap, .obj_id = 1178 /* frame_signtx_group_bin_0308 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{185, {.type = CDL_FrameCap, .obj_id = 1011 /* frame_signtx_group_bin_0129 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{186, {.type = CDL_FrameCap, .obj_id = 900 /* frame_signtx_group_bin_0005 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{187, {.type = CDL_FrameCap, .obj_id = 978 /* frame_signtx_group_bin_0093 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{188, {.type = CDL_FrameCap, .obj_id = 1110 /* frame_signtx_group_bin_0236 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{189, {.type = CDL_FrameCap, .obj_id = 946 /* frame_signtx_group_bin_0056 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{190, {.type = CDL_FrameCap, .obj_id = 1079 /* frame_signtx_group_bin_0203 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{191, {.type = CDL_FrameCap, .obj_id = 916 /* frame_signtx_group_bin_0021 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{192, {.type = CDL_FrameCap, .obj_id = 927 /* frame_signtx_group_bin_0032 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{193, {.type = CDL_FrameCap, .obj_id = 1183 /* frame_signtx_group_bin_0313 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{194, {.type = CDL_FrameCap, .obj_id = 1097 /* frame_signtx_group_bin_0222 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{195, {.type = CDL_FrameCap, .obj_id = 1185 /* frame_signtx_group_bin_0315 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{196, {.type = CDL_FrameCap, .obj_id = 970 /* frame_signtx_group_bin_0085 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{197, {.type = CDL_FrameCap, .obj_id = 1117 /* frame_signtx_group_bin_0243 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{198, {.type = CDL_FrameCap, .obj_id = 1144 /* frame_signtx_group_bin_0272 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{199, {.type = CDL_FrameCap, .obj_id = 933 /* frame_signtx_group_bin_0042 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{200, {.type = CDL_FrameCap, .obj_id = 1020 /* frame_signtx_group_bin_0139 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{201, {.type = CDL_FrameCap, .obj_id = 1103 /* frame_signtx_group_bin_0229 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{202, {.type = CDL_FrameCap, .obj_id = 1191 /* frame_signtx_group_bin_0323 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{203, {.type = CDL_FrameCap, .obj_id = 979 /* frame_signtx_group_bin_0094 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{204, {.type = CDL_FrameCap, .obj_id = 1065 /* frame_signtx_group_bin_0189 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{205, {.type = CDL_FrameCap, .obj_id = 1152 /* frame_signtx_group_bin_0280 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{206, {.type = CDL_FrameCap, .obj_id = 939 /* frame_signtx_group_bin_0048 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{207, {.type = CDL_FrameCap, .obj_id = 1026 /* frame_signtx_group_bin_0145 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{208, {.type = CDL_FrameCap, .obj_id = 1112 /* frame_signtx_group_bin_0238 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{209, {.type = CDL_FrameCap, .obj_id = 902 /* frame_signtx_group_bin_0007 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{210, {.type = CDL_FrameCap, .obj_id = 986 /* frame_signtx_group_bin_0101 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{211, {.type = CDL_FrameCap, .obj_id = 1072 /* frame_signtx_group_bin_0196 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{212, {.type = CDL_FrameCap, .obj_id = 1160 /* frame_signtx_group_bin_0289 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{213, {.type = CDL_FrameCap, .obj_id = 947 /* frame_signtx_group_bin_0057 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{214, {.type = CDL_FrameCap, .obj_id = 1033 /* frame_signtx_group_bin_0153 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{215, {.type = CDL_FrameCap, .obj_id = 1120 /* frame_signtx_group_bin_0246 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{216, {.type = CDL_FrameCap, .obj_id = 963 /* frame_signtx_group_bin_0076 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{217, {.type = CDL_FrameCap, .obj_id = 1014 /* frame_signtx_group_bin_0132 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{218, {.type = CDL_FrameCap, .obj_id = 1081 /* frame_signtx_group_bin_0205 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{219, {.type = CDL_FrameCap, .obj_id = 1064 /* frame_signtx_group_bin_0188 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{220, {.type = CDL_FrameCap, .obj_id = 901 /* frame_signtx_group_bin_0006 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{221, {.type = CDL_FrameCap, .obj_id = 1032 /* frame_signtx_group_bin_0152 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{222, {.type = CDL_FrameCap, .obj_id = 1167 /* frame_signtx_group_bin_0296 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{223, {.type = CDL_FrameCap, .obj_id = 1001 /* frame_signtx_group_bin_0119 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{224, {.type = CDL_FrameCap, .obj_id = 1003 /* frame_signtx_group_bin_0121 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{225, {.type = CDL_FrameCap, .obj_id = 1088 /* frame_signtx_group_bin_0212 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{226, {.type = CDL_FrameCap, .obj_id = 1176 /* frame_signtx_group_bin_0306 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{227, {.type = CDL_FrameCap, .obj_id = 961 /* frame_signtx_group_bin_0074 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{228, {.type = CDL_FrameCap, .obj_id = 1049 /* frame_signtx_group_bin_0170 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{229, {.type = CDL_FrameCap, .obj_id = 1135 /* frame_signtx_group_bin_0263 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{230, {.type = CDL_FrameCap, .obj_id = 1012 /* frame_signtx_group_bin_0130 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{231, {.type = CDL_FrameCap, .obj_id = 1009 /* frame_signtx_group_bin_0127 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{232, {.type = CDL_FrameCap, .obj_id = 1095 /* frame_signtx_group_bin_0219 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{233, {.type = CDL_FrameCap, .obj_id = 1139 /* frame_signtx_group_bin_0267 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{234, {.type = CDL_FrameCap, .obj_id = 968 /* frame_signtx_group_bin_0083 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{235, {.type = CDL_FrameCap, .obj_id = 1056 /* frame_signtx_group_bin_0179 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{236, {.type = CDL_FrameCap, .obj_id = 1141 /* frame_signtx_group_bin_0269 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{237, {.type = CDL_FrameCap, .obj_id = 931 /* frame_signtx_group_bin_0039 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{238, {.type = CDL_FrameCap, .obj_id = 1017 /* frame_signtx_group_bin_0136 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{239, {.type = CDL_FrameCap, .obj_id = 1101 /* frame_signtx_group_bin_0226 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{240, {.type = CDL_FrameCap, .obj_id = 1189 /* frame_signtx_group_bin_0321 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{241, {.type = CDL_FrameCap, .obj_id = 976 /* frame_signtx_group_bin_0091 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{242, {.type = CDL_FrameCap, .obj_id = 1062 /* frame_signtx_group_bin_0186 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{243, {.type = CDL_FrameCap, .obj_id = 1149 /* frame_signtx_group_bin_0277 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{244, {.type = CDL_FrameCap, .obj_id = 937 /* frame_signtx_group_bin_0046 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{245, {.type = CDL_FrameCap, .obj_id = 1024 /* frame_signtx_group_bin_0143 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{246, {.type = CDL_FrameCap, .obj_id = 1108 /* frame_signtx_group_bin_0234 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{247, {.type = CDL_FrameCap, .obj_id = 998 /* frame_signtx_group_bin_0116 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{248, {.type = CDL_FrameCap, .obj_id = 1051 /* frame_signtx_group_bin_0172 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{249, {.type = CDL_FrameCap, .obj_id = 1147 /* frame_signtx_group_bin_0275 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{250, {.type = CDL_FrameCap, .obj_id = 1019 /* frame_signtx_group_bin_0138 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{251, {.type = CDL_FrameCap, .obj_id = 1151 /* frame_signtx_group_bin_0279 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{252, {.type = CDL_FrameCap, .obj_id = 985 /* frame_signtx_group_bin_0100 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{253, {.type = CDL_FrameCap, .obj_id = 1119 /* frame_signtx_group_bin_0245 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{254, {.type = CDL_FrameCap, .obj_id = 953 /* frame_signtx_group_bin_0063 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{255, {.type = CDL_FrameCap, .obj_id = 1086 /* frame_signtx_group_bin_0210 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{256, {.type = CDL_FrameCap, .obj_id = 925 /* frame_signtx_group_bin_0030 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{257, {.type = CDL_FrameCap, .obj_id = 1057 /* frame_signtx_group_bin_0180 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{258, {.type = CDL_FrameCap, .obj_id = 1107 /* frame_signtx_group_bin_0233 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{259, {.type = CDL_FrameCap, .obj_id = 1039 /* frame_signtx_group_bin_0160 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{260, {.type = CDL_FrameCap, .obj_id = 1157 /* frame_signtx_group_bin_0285 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{261, {.type = CDL_FrameCap, .obj_id = 991 /* frame_signtx_group_bin_0107 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{262, {.type = CDL_FrameCap, .obj_id = 1125 /* frame_signtx_group_bin_0252 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{263, {.type = CDL_FrameCap, .obj_id = 1169 /* frame_signtx_group_bin_0298 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{264, {.type = CDL_FrameCap, .obj_id = 1174 /* frame_signtx_group_bin_0304 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{265, {.type = CDL_FrameCap, .obj_id = 959 /* frame_signtx_group_bin_0072 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{266, {.type = CDL_FrameCap, .obj_id = 1046 /* frame_signtx_group_bin_0167 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{267, {.type = CDL_FrameCap, .obj_id = 1133 /* frame_signtx_group_bin_0261 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{268, {.type = CDL_FrameCap, .obj_id = 922 /* frame_signtx_group_bin_0027 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{269, {.type = CDL_FrameCap, .obj_id = 1007 /* frame_signtx_group_bin_0125 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{270, {.type = CDL_FrameCap, .obj_id = 1093 /* frame_signtx_group_bin_0217 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{271, {.type = CDL_FrameCap, .obj_id = 1181 /* frame_signtx_group_bin_0311 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{272, {.type = CDL_FrameCap, .obj_id = 966 /* frame_signtx_group_bin_0080 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{273, {.type = CDL_FrameCap, .obj_id = 1054 /* frame_signtx_group_bin_0177 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{274, {.type = CDL_FrameCap, .obj_id = 994 /* frame_signtx_group_bin_0111 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{275, {.type = CDL_FrameCap, .obj_id = 929 /* frame_signtx_group_bin_0037 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{276, {.type = CDL_FrameCap, .obj_id = 1015 /* frame_signtx_group_bin_0133 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{277, {.type = CDL_FrameCap, .obj_id = 1099 /* frame_signtx_group_bin_0224 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{278, {.type = CDL_FrameCap, .obj_id = 1187 /* frame_signtx_group_bin_0319 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{279, {.type = CDL_FrameCap, .obj_id = 974 /* frame_signtx_group_bin_0089 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{280, {.type = CDL_FrameCap, .obj_id = 1137 /* frame_signtx_group_bin_0265 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{281, {.type = CDL_FrameCap, .obj_id = 971 /* frame_signtx_group_bin_0086 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{282, {.type = CDL_FrameCap, .obj_id = 1052 /* frame_signtx_group_bin_0174 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{283, {.type = CDL_FrameCap, .obj_id = 983 /* frame_signtx_group_bin_0098 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{284, {.type = CDL_FrameCap, .obj_id = 1071 /* frame_signtx_group_bin_0195 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{285, {.type = CDL_FrameCap, .obj_id = 909 /* frame_signtx_group_bin_0014 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{286, {.type = CDL_FrameCap, .obj_id = 1040 /* frame_signtx_group_bin_0161 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{287, {.type = CDL_FrameCap, .obj_id = 1068 /* frame_signtx_group_bin_0192 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{288, {.type = CDL_FrameCap, .obj_id = 1156 /* frame_signtx_group_bin_0284 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{289, {.type = CDL_FrameCap, .obj_id = 1142 /* frame_signtx_group_bin_0270 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{290, {.type = CDL_FrameCap, .obj_id = 1111 /* frame_signtx_group_bin_0237 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{291, {.type = CDL_FrameCap, .obj_id = 919 /* frame_signtx_group_bin_0024 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{292, {.type = CDL_FrameCap, .obj_id = 944 /* frame_signtx_group_bin_0054 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{293, {.type = CDL_FrameCap, .obj_id = 1077 /* frame_signtx_group_bin_0201 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{294, {.type = CDL_FrameCap, .obj_id = 914 /* frame_signtx_group_bin_0019 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{295, {.type = CDL_FrameCap, .obj_id = 1164 /* frame_signtx_group_bin_0293 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{296, {.type = CDL_FrameCap, .obj_id = 1132 /* frame_signtx_group_bin_0260 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{297, {.type = CDL_FrameCap, .obj_id = 904 /* frame_signtx_group_bin_0009 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{299, {.type = CDL_FrameCap, .obj_id = 1253 /* stack__camkes_stack_signtx_0_control_0_signtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{300, {.type = CDL_FrameCap, .obj_id = 1254 /* stack__camkes_stack_signtx_0_control_1_signtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{301, {.type = CDL_FrameCap, .obj_id = 1255 /* stack__camkes_stack_signtx_0_control_2_signtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{302, {.type = CDL_FrameCap, .obj_id = 1256 /* stack__camkes_stack_signtx_0_control_3_signtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{305, {.type = CDL_FrameCap, .obj_id = 1261 /* stack__camkes_stack_signtx_signtx_iface_0000_0_signtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{306, {.type = CDL_FrameCap, .obj_id = 1262 /* stack__camkes_stack_signtx_signtx_iface_0000_1_signtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{307, {.type = CDL_FrameCap, .obj_id = 1263 /* stack__camkes_stack_signtx_signtx_iface_0000_2_signtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{308, {.type = CDL_FrameCap, .obj_id = 1264 /* stack__camkes_stack_signtx_signtx_iface_0000_3_signtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{311, {.type = CDL_FrameCap, .obj_id = 1257 /* stack__camkes_stack_signtx_0_fault_handler_0000_0_signtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{312, {.type = CDL_FrameCap, .obj_id = 1258 /* stack__camkes_stack_signtx_0_fault_handler_0000_1_signtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{313, {.type = CDL_FrameCap, .obj_id = 1259 /* stack__camkes_stack_signtx_0_fault_handler_0000_2_signtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{314, {.type = CDL_FrameCap, .obj_id = 1260 /* stack__camkes_stack_signtx_0_fault_handler_0000_3_signtx_obj */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{317, {.type = CDL_FrameCap, .obj_id = 1213 /* signtx_frame__camkes_ipc_buffer_signtx_0_control */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{320, {.type = CDL_FrameCap, .obj_id = 1215 /* signtx_frame__camkes_ipc_buffer_signtx_signtx_iface_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},
{323, {.type = CDL_FrameCap, .obj_id = 1214 /* signtx_frame__camkes_ipc_buffer_signtx_0_fault_handler_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},

},
},
[1213] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "signtx_frame__camkes_ipc_buffer_signtx_0_control",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1214] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "signtx_frame__camkes_ipc_buffer_signtx_0_fault_handler_0000",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1215] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "signtx_frame__camkes_ipc_buffer_signtx_signtx_iface_0000",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1216] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "signtx_group_bin_pd",
#endif
.type = CDL_PML4,
.slots.num = 1,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_PDPTCap, .obj_id = 1208 /* pdpt_signtx_group_bin_0000 */, .is_orig = true}},

},
},
[1217] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_crypto_0_control_0_crypto_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1218] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_crypto_0_control_1_crypto_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1219] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_crypto_0_control_2_crypto_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1220] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_crypto_0_control_3_crypto_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1221] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_crypto_0_fault_handler_0000_0_crypto_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1222] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_crypto_0_fault_handler_0000_1_crypto_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1223] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_crypto_0_fault_handler_0000_2_crypto_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1224] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_crypto_0_fault_handler_0000_3_crypto_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1225] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_crypto_crypto_iface_0000_0_crypto_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1226] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_crypto_crypto_iface_0000_1_crypto_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1227] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_crypto_crypto_iface_0000_2_crypto_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1228] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_crypto_crypto_iface_0000_3_crypto_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1229] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modchk_0_control_0_modchk_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1230] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modchk_0_control_1_modchk_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1231] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modchk_0_control_2_modchk_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1232] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modchk_0_control_3_modchk_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1233] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modchk_0_fault_handler_0000_0_modchk_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1234] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modchk_0_fault_handler_0000_1_modchk_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1235] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modchk_0_fault_handler_0000_2_modchk_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1236] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modchk_0_fault_handler_0000_3_modchk_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1237] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modchk_modchk_iface_0000_0_modchk_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1238] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modchk_modchk_iface_0000_1_modchk_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1239] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modchk_modchk_iface_0000_2_modchk_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1240] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modchk_modchk_iface_0000_3_modchk_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1241] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modtx_0_control_0_modtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1242] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modtx_0_control_1_modtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1243] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modtx_0_control_2_modtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1244] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modtx_0_control_3_modtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1245] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modtx_0_fault_handler_0000_0_modtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1246] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modtx_0_fault_handler_0000_1_modtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1247] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modtx_0_fault_handler_0000_2_modtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1248] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modtx_0_fault_handler_0000_3_modtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1249] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modtx_modtx_iface_0000_0_modtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1250] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modtx_modtx_iface_0000_1_modtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1251] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modtx_modtx_iface_0000_2_modtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1252] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_modtx_modtx_iface_0000_3_modtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1253] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_signtx_0_control_0_signtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1254] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_signtx_0_control_1_signtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1255] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_signtx_0_control_2_signtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1256] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_signtx_0_control_3_signtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1257] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_signtx_0_fault_handler_0000_0_signtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1258] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_signtx_0_fault_handler_0000_1_signtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1259] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_signtx_0_fault_handler_0000_2_signtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1260] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_signtx_0_fault_handler_0000_3_signtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1261] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_signtx_signtx_iface_0000_0_signtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1262] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_signtx_signtx_iface_0000_1_signtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1263] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_signtx_signtx_iface_0000_2_signtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1264] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "stack__camkes_stack_signtx_signtx_iface_0000_3_signtx_obj",
#endif
.type = CDL_Frame,
.size_bits = 12.0,
.paddr = (void*)0x0,
},
[1265] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "crypto_6_0_control_9_tcb",
#endif
.type = CDL_TCB,
.tcb_extra = {
#if (5495808 & ((1 << 9) - 1)) != 0
#    error "IPC buffer not 512-byte aligned"
#endif
.ipcbuffer_addr_upper_bits = 5495808 >> 9,
.priority = 254,
.max_priority = 254,
.affinity = 0,
.pc = 4225329,
.sp = 5435392,
.elf_name = "crypto_group_bin",
.init = (const seL4_Word[]){1},
.init_sz = 1,
.domain = 0,
.fault_ep = 2,
},
.slots.num = 3,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_CNodeCap, .obj_id = 1277 /* crypto_cnode */, .is_orig = true, .rights = CDL_AllRights, .data = CDL_CapData_MakeGuard(60, 0)}},
{1, {.type = CDL_PML4Cap, .obj_id = 3 /* crypto_group_bin_pd */, .is_orig = true}},
{4, {.type = CDL_FrameCap, .obj_id = 0 /* crypto_frame__camkes_ipc_buffer_crypto_0_control */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},

},
},
[1266] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "crypto_6_0_fault_handler_15_0000_tcb",
#endif
.type = CDL_TCB,
.tcb_extra = {
#if (5520384 & ((1 << 9) - 1)) != 0
#    error "IPC buffer not 512-byte aligned"
#endif
.ipcbuffer_addr_upper_bits = 5520384 >> 9,
.priority = 254,
.max_priority = 254,
.affinity = 0,
.pc = 4225329,
.sp = 5484544,
.elf_name = "crypto_group_bin",
.init = (const seL4_Word[]){5},
.init_sz = 1,
.domain = 0,
.fault_ep = 0,
},
.slots.num = 3,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_CNodeCap, .obj_id = 1277 /* crypto_cnode */, .is_orig = true, .rights = CDL_AllRights, .data = CDL_CapData_MakeGuard(60, 0)}},
{1, {.type = CDL_PML4Cap, .obj_id = 3 /* crypto_group_bin_pd */, .is_orig = true}},
{4, {.type = CDL_FrameCap, .obj_id = 1 /* crypto_frame__camkes_ipc_buffer_crypto_0_fault_handler_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},

},
},
[1267] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "crypto_6_crypto_iface_12_0000_tcb",
#endif
.type = CDL_TCB,
.tcb_extra = {
#if (5508096 & ((1 << 9) - 1)) != 0
#    error "IPC buffer not 512-byte aligned"
#endif
.ipcbuffer_addr_upper_bits = 5508096 >> 9,
.priority = 254,
.max_priority = 254,
.affinity = 0,
.pc = 4225329,
.sp = 5459968,
.elf_name = "crypto_group_bin",
.init = (const seL4_Word[]){3},
.init_sz = 1,
.domain = 0,
.fault_ep = 4,
},
.slots.num = 3,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_CNodeCap, .obj_id = 1277 /* crypto_cnode */, .is_orig = true, .rights = CDL_AllRights, .data = CDL_CapData_MakeGuard(60, 0)}},
{1, {.type = CDL_PML4Cap, .obj_id = 3 /* crypto_group_bin_pd */, .is_orig = true}},
{4, {.type = CDL_FrameCap, .obj_id = 2 /* crypto_frame__camkes_ipc_buffer_crypto_crypto_iface_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},

},
},
[1268] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modchk_6_0_control_9_tcb",
#endif
.type = CDL_TCB,
.tcb_extra = {
#if (5491712 & ((1 << 9) - 1)) != 0
#    error "IPC buffer not 512-byte aligned"
#endif
.ipcbuffer_addr_upper_bits = 5491712 >> 9,
.priority = 254,
.max_priority = 254,
.affinity = 0,
.pc = 4222685,
.sp = 5431296,
.elf_name = "modchk_group_bin",
.init = (const seL4_Word[]){1},
.init_sz = 1,
.domain = 0,
.fault_ep = 2,
},
.slots.num = 3,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_CNodeCap, .obj_id = 1278 /* modchk_cnode */, .is_orig = true, .rights = CDL_AllRights, .data = CDL_CapData_MakeGuard(60, 0)}},
{1, {.type = CDL_PML4Cap, .obj_id = 1196 /* modchk_group_bin_pd */, .is_orig = true}},
{4, {.type = CDL_FrameCap, .obj_id = 1193 /* modchk_frame__camkes_ipc_buffer_modchk_0_control */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},

},
},
[1269] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modchk_6_0_fault_handler_15_0000_tcb",
#endif
.type = CDL_TCB,
.tcb_extra = {
#if (5516288 & ((1 << 9) - 1)) != 0
#    error "IPC buffer not 512-byte aligned"
#endif
.ipcbuffer_addr_upper_bits = 5516288 >> 9,
.priority = 254,
.max_priority = 254,
.affinity = 0,
.pc = 4222685,
.sp = 5480448,
.elf_name = "modchk_group_bin",
.init = (const seL4_Word[]){5},
.init_sz = 1,
.domain = 0,
.fault_ep = 0,
},
.slots.num = 3,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_CNodeCap, .obj_id = 1278 /* modchk_cnode */, .is_orig = true, .rights = CDL_AllRights, .data = CDL_CapData_MakeGuard(60, 0)}},
{1, {.type = CDL_PML4Cap, .obj_id = 1196 /* modchk_group_bin_pd */, .is_orig = true}},
{4, {.type = CDL_FrameCap, .obj_id = 1194 /* modchk_frame__camkes_ipc_buffer_modchk_0_fault_handler_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},

},
},
[1270] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modchk_6_modchk_iface_12_0000_tcb",
#endif
.type = CDL_TCB,
.tcb_extra = {
#if (5504000 & ((1 << 9) - 1)) != 0
#    error "IPC buffer not 512-byte aligned"
#endif
.ipcbuffer_addr_upper_bits = 5504000 >> 9,
.priority = 254,
.max_priority = 254,
.affinity = 0,
.pc = 4222685,
.sp = 5455872,
.elf_name = "modchk_group_bin",
.init = (const seL4_Word[]){3},
.init_sz = 1,
.domain = 0,
.fault_ep = 4,
},
.slots.num = 3,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_CNodeCap, .obj_id = 1278 /* modchk_cnode */, .is_orig = true, .rights = CDL_AllRights, .data = CDL_CapData_MakeGuard(60, 0)}},
{1, {.type = CDL_PML4Cap, .obj_id = 1196 /* modchk_group_bin_pd */, .is_orig = true}},
{4, {.type = CDL_FrameCap, .obj_id = 1195 /* modchk_frame__camkes_ipc_buffer_modchk_modchk_iface_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},

},
},
[1271] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modtx_5_0_control_9_tcb",
#endif
.type = CDL_TCB,
.tcb_extra = {
#if (5487616 & ((1 << 9) - 1)) != 0
#    error "IPC buffer not 512-byte aligned"
#endif
.ipcbuffer_addr_upper_bits = 5487616 >> 9,
.priority = 254,
.max_priority = 254,
.affinity = 0,
.pc = 4220942,
.sp = 5427200,
.elf_name = "modtx_group_bin",
.init = (const seL4_Word[]){1},
.init_sz = 1,
.domain = 0,
.fault_ep = 2,
},
.slots.num = 3,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_CNodeCap, .obj_id = 1279 /* modtx_cnode */, .is_orig = true, .rights = CDL_AllRights, .data = CDL_CapData_MakeGuard(60, 0)}},
{1, {.type = CDL_PML4Cap, .obj_id = 1200 /* modtx_group_bin_pd */, .is_orig = true}},
{4, {.type = CDL_FrameCap, .obj_id = 1197 /* modtx_frame__camkes_ipc_buffer_modtx_0_control */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},

},
},
[1272] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modtx_5_0_fault_handler_15_0000_tcb",
#endif
.type = CDL_TCB,
.tcb_extra = {
#if (5512192 & ((1 << 9) - 1)) != 0
#    error "IPC buffer not 512-byte aligned"
#endif
.ipcbuffer_addr_upper_bits = 5512192 >> 9,
.priority = 254,
.max_priority = 254,
.affinity = 0,
.pc = 4220942,
.sp = 5476352,
.elf_name = "modtx_group_bin",
.init = (const seL4_Word[]){5},
.init_sz = 1,
.domain = 0,
.fault_ep = 0,
},
.slots.num = 3,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_CNodeCap, .obj_id = 1279 /* modtx_cnode */, .is_orig = true, .rights = CDL_AllRights, .data = CDL_CapData_MakeGuard(60, 0)}},
{1, {.type = CDL_PML4Cap, .obj_id = 1200 /* modtx_group_bin_pd */, .is_orig = true}},
{4, {.type = CDL_FrameCap, .obj_id = 1198 /* modtx_frame__camkes_ipc_buffer_modtx_0_fault_handler_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},

},
},
[1273] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modtx_5_modtx_iface_11_0000_tcb",
#endif
.type = CDL_TCB,
.tcb_extra = {
#if (5499904 & ((1 << 9) - 1)) != 0
#    error "IPC buffer not 512-byte aligned"
#endif
.ipcbuffer_addr_upper_bits = 5499904 >> 9,
.priority = 254,
.max_priority = 254,
.affinity = 0,
.pc = 4220942,
.sp = 5451776,
.elf_name = "modtx_group_bin",
.init = (const seL4_Word[]){3},
.init_sz = 1,
.domain = 0,
.fault_ep = 4,
},
.slots.num = 3,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_CNodeCap, .obj_id = 1279 /* modtx_cnode */, .is_orig = true, .rights = CDL_AllRights, .data = CDL_CapData_MakeGuard(60, 0)}},
{1, {.type = CDL_PML4Cap, .obj_id = 1200 /* modtx_group_bin_pd */, .is_orig = true}},
{4, {.type = CDL_FrameCap, .obj_id = 1199 /* modtx_frame__camkes_ipc_buffer_modtx_modtx_iface_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},

},
},
[1274] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "signtx_6_0_control_9_tcb",
#endif
.type = CDL_TCB,
.tcb_extra = {
#if (5495808 & ((1 << 9) - 1)) != 0
#    error "IPC buffer not 512-byte aligned"
#endif
.ipcbuffer_addr_upper_bits = 5495808 >> 9,
.priority = 254,
.max_priority = 254,
.affinity = 0,
.pc = 4225972,
.sp = 5435392,
.elf_name = "signtx_group_bin",
.init = (const seL4_Word[]){1},
.init_sz = 1,
.domain = 0,
.fault_ep = 2,
},
.slots.num = 3,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_CNodeCap, .obj_id = 1280 /* signtx_cnode */, .is_orig = true, .rights = CDL_AllRights, .data = CDL_CapData_MakeGuard(60, 0)}},
{1, {.type = CDL_PML4Cap, .obj_id = 1216 /* signtx_group_bin_pd */, .is_orig = true}},
{4, {.type = CDL_FrameCap, .obj_id = 1213 /* signtx_frame__camkes_ipc_buffer_signtx_0_control */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},

},
},
[1275] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "signtx_6_0_fault_handler_15_0000_tcb",
#endif
.type = CDL_TCB,
.tcb_extra = {
#if (5520384 & ((1 << 9) - 1)) != 0
#    error "IPC buffer not 512-byte aligned"
#endif
.ipcbuffer_addr_upper_bits = 5520384 >> 9,
.priority = 254,
.max_priority = 254,
.affinity = 0,
.pc = 4225972,
.sp = 5484544,
.elf_name = "signtx_group_bin",
.init = (const seL4_Word[]){5},
.init_sz = 1,
.domain = 0,
.fault_ep = 0,
},
.slots.num = 3,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_CNodeCap, .obj_id = 1280 /* signtx_cnode */, .is_orig = true, .rights = CDL_AllRights, .data = CDL_CapData_MakeGuard(60, 0)}},
{1, {.type = CDL_PML4Cap, .obj_id = 1216 /* signtx_group_bin_pd */, .is_orig = true}},
{4, {.type = CDL_FrameCap, .obj_id = 1214 /* signtx_frame__camkes_ipc_buffer_signtx_0_fault_handler_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},

},
},
[1276] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "signtx_6_signtx_iface_12_0000_tcb",
#endif
.type = CDL_TCB,
.tcb_extra = {
#if (5508096 & ((1 << 9) - 1)) != 0
#    error "IPC buffer not 512-byte aligned"
#endif
.ipcbuffer_addr_upper_bits = 5508096 >> 9,
.priority = 254,
.max_priority = 254,
.affinity = 0,
.pc = 4225972,
.sp = 5459968,
.elf_name = "signtx_group_bin",
.init = (const seL4_Word[]){3},
.init_sz = 1,
.domain = 0,
.fault_ep = 4,
},
.slots.num = 3,
.slots.slot = (CDL_CapSlot[]) {
{0, {.type = CDL_CNodeCap, .obj_id = 1280 /* signtx_cnode */, .is_orig = true, .rights = CDL_AllRights, .data = CDL_CapData_MakeGuard(60, 0)}},
{1, {.type = CDL_PML4Cap, .obj_id = 1216 /* signtx_group_bin_pd */, .is_orig = true}},
{4, {.type = CDL_FrameCap, .obj_id = 1215 /* signtx_frame__camkes_ipc_buffer_signtx_signtx_iface_0000 */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .vm_attribs = seL4_ARCH_Default_VMAttributes, .mapping_container_id = INVALID_OBJ_ID, .mapping_slot = 0}},

},
},
[1277] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "crypto_cnode",
#endif
.type = CDL_CNode,
.size_bits = 4,
.slots.num = 13,
.slots.slot = (CDL_CapSlot[]) {
{1, {.type = CDL_TCBCap, .obj_id = 1265 /* crypto_6_0_control_9_tcb */, .is_orig = true, .rights = CDL_AllRights}},
{2, {.type = CDL_EPCap, .obj_id = 1285 /* crypto_fault_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 1}}},
{3, {.type = CDL_TCBCap, .obj_id = 1267 /* crypto_6_crypto_iface_12_0000_tcb */, .is_orig = true, .rights = CDL_AllRights}},
{4, {.type = CDL_EPCap, .obj_id = 1285 /* crypto_fault_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 3}}},
{5, {.type = CDL_TCBCap, .obj_id = 1266 /* crypto_6_0_fault_handler_15_0000_tcb */, .is_orig = true, .rights = CDL_AllRights}},
{6, {.type = CDL_EPCap, .obj_id = 1285 /* crypto_fault_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{7, {.type = CDL_EPCap, .obj_id = 1288 /* crypto_pre_init_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{8, {.type = CDL_EPCap, .obj_id = 1286 /* crypto_interface_init_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{9, {.type = CDL_EPCap, .obj_id = 1287 /* crypto_post_init_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{10, {.type = CDL_EPCap, .obj_id = 1282 /* conn2.conn5_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{11, {.type = CDL_CNodeCap, .obj_id = 1277 /* crypto_cnode */, .is_orig = true, .rights = CDL_AllRights, .data = CDL_CapData_MakeGuard(60, 0)}},
{13, {.type = CDL_EPCap, .obj_id = 1283 /* conn3.conn7_ep */, .is_orig = true, .rights = (0|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 1}}},
{14, {.type = CDL_EPCap, .obj_id = 1284 /* conn4.conn8_ep */, .is_orig = true, .rights = (0|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 1}}},

},
},
[1278] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modchk_cnode",
#endif
.type = CDL_CNode,
.size_bits = 4,
.slots.num = 13,
.slots.slot = (CDL_CapSlot[]) {
{1, {.type = CDL_TCBCap, .obj_id = 1268 /* modchk_6_0_control_9_tcb */, .is_orig = true, .rights = CDL_AllRights}},
{2, {.type = CDL_EPCap, .obj_id = 1289 /* modchk_fault_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 1}}},
{3, {.type = CDL_TCBCap, .obj_id = 1270 /* modchk_6_modchk_iface_12_0000_tcb */, .is_orig = true, .rights = CDL_AllRights}},
{4, {.type = CDL_EPCap, .obj_id = 1289 /* modchk_fault_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 3}}},
{5, {.type = CDL_TCBCap, .obj_id = 1269 /* modchk_6_0_fault_handler_15_0000_tcb */, .is_orig = true, .rights = CDL_AllRights}},
{6, {.type = CDL_EPCap, .obj_id = 1289 /* modchk_fault_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{7, {.type = CDL_EPCap, .obj_id = 1292 /* modchk_pre_init_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{8, {.type = CDL_EPCap, .obj_id = 1290 /* modchk_interface_init_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{9, {.type = CDL_EPCap, .obj_id = 1291 /* modchk_post_init_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{10, {.type = CDL_EPCap, .obj_id = 1281 /* conn1.conn6_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{11, {.type = CDL_CNodeCap, .obj_id = 1278 /* modchk_cnode */, .is_orig = true, .rights = CDL_AllRights, .data = CDL_CapData_MakeGuard(60, 0)}},
{13, {.type = CDL_EPCap, .obj_id = 1283 /* conn3.conn7_ep */, .is_orig = true, .rights = (0|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 2}}},
{14, {.type = CDL_EPCap, .obj_id = 1284 /* conn4.conn8_ep */, .is_orig = true, .rights = (0|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 2}}},

},
},
[1279] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modtx_cnode",
#endif
.type = CDL_CNode,
.size_bits = 4,
.slots.num = 13,
.slots.slot = (CDL_CapSlot[]) {
{1, {.type = CDL_TCBCap, .obj_id = 1271 /* modtx_5_0_control_9_tcb */, .is_orig = true, .rights = CDL_AllRights}},
{2, {.type = CDL_EPCap, .obj_id = 1293 /* modtx_fault_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 1}}},
{3, {.type = CDL_TCBCap, .obj_id = 1273 /* modtx_5_modtx_iface_11_0000_tcb */, .is_orig = true, .rights = CDL_AllRights}},
{4, {.type = CDL_EPCap, .obj_id = 1293 /* modtx_fault_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 3}}},
{5, {.type = CDL_TCBCap, .obj_id = 1272 /* modtx_5_0_fault_handler_15_0000_tcb */, .is_orig = true, .rights = CDL_AllRights}},
{6, {.type = CDL_EPCap, .obj_id = 1293 /* modtx_fault_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{7, {.type = CDL_EPCap, .obj_id = 1296 /* modtx_pre_init_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{8, {.type = CDL_EPCap, .obj_id = 1294 /* modtx_interface_init_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{9, {.type = CDL_EPCap, .obj_id = 1295 /* modtx_post_init_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{10, {.type = CDL_EPCap, .obj_id = 1282 /* conn2.conn5_ep */, .is_orig = true, .rights = (0|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 1}}},
{11, {.type = CDL_EPCap, .obj_id = 1281 /* conn1.conn6_ep */, .is_orig = true, .rights = (0|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 1}}},
{12, {.type = CDL_EPCap, .obj_id = 1283 /* conn3.conn7_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{13, {.type = CDL_CNodeCap, .obj_id = 1279 /* modtx_cnode */, .is_orig = true, .rights = CDL_AllRights, .data = CDL_CapData_MakeGuard(60, 0)}},

},
},
[1280] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "signtx_cnode",
#endif
.type = CDL_CNode,
.size_bits = 4,
.slots.num = 13,
.slots.slot = (CDL_CapSlot[]) {
{1, {.type = CDL_TCBCap, .obj_id = 1274 /* signtx_6_0_control_9_tcb */, .is_orig = true, .rights = CDL_AllRights}},
{2, {.type = CDL_EPCap, .obj_id = 1297 /* signtx_fault_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 1}}},
{3, {.type = CDL_TCBCap, .obj_id = 1276 /* signtx_6_signtx_iface_12_0000_tcb */, .is_orig = true, .rights = CDL_AllRights}},
{4, {.type = CDL_EPCap, .obj_id = 1297 /* signtx_fault_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 3}}},
{5, {.type = CDL_TCBCap, .obj_id = 1275 /* signtx_6_0_fault_handler_15_0000_tcb */, .is_orig = true, .rights = CDL_AllRights}},
{6, {.type = CDL_EPCap, .obj_id = 1297 /* signtx_fault_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{7, {.type = CDL_EPCap, .obj_id = 1300 /* signtx_pre_init_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{8, {.type = CDL_EPCap, .obj_id = 1298 /* signtx_interface_init_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{9, {.type = CDL_EPCap, .obj_id = 1299 /* signtx_post_init_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{10, {.type = CDL_EPCap, .obj_id = 1282 /* conn2.conn5_ep */, .is_orig = true, .rights = (0|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 2}}},
{11, {.type = CDL_EPCap, .obj_id = 1281 /* conn1.conn6_ep */, .is_orig = true, .rights = (0|CDL_CanWrite|CDL_CanGrant), .data = { .tag = CDL_CapData_Badge, .badge = 2}}},
{12, {.type = CDL_EPCap, .obj_id = 1284 /* conn4.conn8_ep */, .is_orig = true, .rights = (0|CDL_CanRead|CDL_CanWrite), .data = { .tag = CDL_CapData_Badge, .badge = 0}}},
{13, {.type = CDL_CNodeCap, .obj_id = 1280 /* signtx_cnode */, .is_orig = true, .rights = CDL_AllRights, .data = CDL_CapData_MakeGuard(60, 0)}},

},
},
[1281] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "conn1.conn6_ep",
#endif
.type = CDL_Endpoint,
},
[1282] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "conn2.conn5_ep",
#endif
.type = CDL_Endpoint,
},
[1283] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "conn3.conn7_ep",
#endif
.type = CDL_Endpoint,
},
[1284] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "conn4.conn8_ep",
#endif
.type = CDL_Endpoint,
},
[1285] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "crypto_fault_ep",
#endif
.type = CDL_Endpoint,
},
[1286] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "crypto_interface_init_ep",
#endif
.type = CDL_Endpoint,
},
[1287] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "crypto_post_init_ep",
#endif
.type = CDL_Endpoint,
},
[1288] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "crypto_pre_init_ep",
#endif
.type = CDL_Endpoint,
},
[1289] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modchk_fault_ep",
#endif
.type = CDL_Endpoint,
},
[1290] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modchk_interface_init_ep",
#endif
.type = CDL_Endpoint,
},
[1291] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modchk_post_init_ep",
#endif
.type = CDL_Endpoint,
},
[1292] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modchk_pre_init_ep",
#endif
.type = CDL_Endpoint,
},
[1293] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modtx_fault_ep",
#endif
.type = CDL_Endpoint,
},
[1294] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modtx_interface_init_ep",
#endif
.type = CDL_Endpoint,
},
[1295] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modtx_post_init_ep",
#endif
.type = CDL_Endpoint,
},
[1296] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "modtx_pre_init_ep",
#endif
.type = CDL_Endpoint,
},
[1297] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "signtx_fault_ep",
#endif
.type = CDL_Endpoint,
},
[1298] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "signtx_interface_init_ep",
#endif
.type = CDL_Endpoint,
},
[1299] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "signtx_post_init_ep",
#endif
.type = CDL_Endpoint,
},
[1300] = {
#ifdef CONFIG_DEBUG_BUILD
.name = "signtx_pre_init_ep",
#endif
.type = CDL_Endpoint,
},

},
.num_frame_fill = 0,
.frame_fill = (CDL_FrameFill[]){

},
};