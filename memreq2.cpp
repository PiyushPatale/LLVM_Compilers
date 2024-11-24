#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include <cstdlib>

using namespace llvm;

namespace
{
    struct MemoryRequirementsPass : public FunctionPass
    {
        static char ID;
        MemoryRequirementsPass() : FunctionPass(ID) {}

        virtual bool runOnFunction(Function &F) override
        {

            std::string MangledName = F.getName().str();

            // Demangle the function name using c++filt
            FILE *pipe = popen(("c++filt -n " + MangledName).c_str(), "r");
            if (!pipe)
            {
                errs() << "Error: Unable to run c++filt\n";
                return false;
            }

            char buffer[128];
            std::string DemangledName = "";
            while (!feof(pipe))
            {
                if (fgets(buffer, 128, pipe) != NULL)
                    DemangledName += buffer;
            }
            pclose(pipe);

            errs() << "Function: " << DemangledName;

            // Code for calculation of memory requirements for each block and Assigning IDs
            int BBID = 1;
            for (BasicBlock &BB : F)
            {
                uint64_t MemRequirements = 0;
                errs() << "Basic Block " << BBID << "\n";

                for (Instruction &I : BB)
                {
                    MemRequirements += sizeof(I);
                }

                errs() << "Memory Requirements: " << MemRequirements << " bytes\n";
                BBID++;
            }
            errs() << "Number of Basic Blocks in this function: " << F.size() << "\n\n";

            return false;
        }
    };
}

char MemoryRequirementsPass::ID = 0;
static RegisterPass<MemoryRequirementsPass> X("memreq2", "Memory Requirements of Basic Blocks", false, false);
