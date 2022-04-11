#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/IRBuilder.h"

#include <vector>

using namespace llvm;

namespace{
struct ir_instrumentation : public ModulePass{
    static char ID;
    Function *monitor;

    ir_instrumentation() : ModulePass(ID) {}

    virtual bool runOnModule(Module &M)
    {
        errs() << "====----- Entered Module " << M.getName() << ".\n";

       

        for(Module::iterator F = M.begin(), E = M.end(); F!= E; ++F)
        {
            errs() << "Function name: " << F->getName() << ".\n";
            if(F->getName() == "print"){
                monitor = cast<Function>(F);
                continue;
            }

            for(Function::iterator BB = F->begin(), E = F->end(); BB != E; ++BB)
            {
               
                    BasicBlock::iterator BI = BB->begin();
                    errs() << "new basic block\n";
                    errs() << "Function name: " << F->getName() << ".\n";
                    errs() << "Basic Block name: " << BB->getName() << ".\n";
                    errs() << "Total name: " << F->getName() <<"_" << BB->getName() << "\n";
                    BasicBlock* bb =  = &*BB
                    errs() << *bb;

                    errs() << "trying to insert  the instructions!\n";
                    IRBuilder<> B(BB);
                    Value *v2 = B.CreateGlobalStringPtr(F->getName(), "str");
                    Value *v1 = B.CreateGlobalStringPtr(BB->getName(), "str");
                    ArrayRef<Value *> args1(v1);
                    Instruction *newInst1 = CallInst::Create(monitor, args1, "");
                    BB->getInstList().insert(BI, newInst1); 
                    ArrayRef<Value *> args1(v2);
                    Instruction *newInst2 = CallInst::Create(monitor, args2, "");
                    BB->getInstList().insert(BI, newInst2); 
                    errs() << "Inserted the instructions!\n";
                    

                
            }
        }

        return true;
    }
};
char ir_instrumentation::ID = 0;
static RegisterPass<ir_instrumentation> X("ir-instrumentation", "LLVM IR Instrumentation Pass");