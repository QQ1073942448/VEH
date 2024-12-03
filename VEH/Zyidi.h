#include <Zydis/Zydis.h>
#include"Ö÷´°¿Ú.h"
#include "afxdialogex.h"
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

    ZyanStatus ZydisDecoderInit(ZydisDecoder* decoder, ZydisMachineMode machine_mode,
        ZydisStackWidth stack_width);

    ZyanStatus ZydisDecoderDecodeFull(const ZydisDecoder* decoder,
        const void* buffer, ZyanUSize length, ZydisDecodedInstruction* instruction,
        ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT]);

    ZyanStatus ZydisFormatterInit(ZydisFormatter* formatter, ZydisFormatterStyle style);

    ZyanStatus ZydisFormatterFormatInstruction(const ZydisFormatter* formatter,
        const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operands,
        ZyanU8 operand_count, char* buffer, ZyanUSize length, ZyanU64 runtime_address,
        void* user_data);

    ZyanStatus ZydisEncoderDecodedInstructionToEncoderRequest(
        const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operands,
        ZyanU8 operand_count_visible, ZydisEncoderRequest* request);
    ZyanStatus ZydisEncoderEncodeInstruction(const ZydisEncoderRequest* request,
        void* buffer, ZyanUSize* length);

#ifdef __cplusplus
}
#endif