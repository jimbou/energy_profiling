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
struct SkeletonPass : public ModulePass{
    static char ID;
    Function *monitor;

    SkeletonPass() : ModulePass(ID) {}

    virtual bool runOnModule(Module &M)
    {
        errs() << "====----- Entered Module " << M.getName() << ".\n";

       //int counter =0;

        for(Module::iterator F = M.begin(), E = M.end(); F!= E; ++F)
        {
            //errs() << "Function name: " << F->getName() << ".\n";
            if(F->getName() == "print"){
                monitor = cast<Function>(F);
                continue;
            }
            

            for(Function::iterator BB = F->begin(), E = F->end(); BB != E; ++BB)
            {
               
                    BasicBlock::iterator BI = BB->begin();
                    errs() << "new basic block\n";
                    errs() << "Function name: " << F->getName() << ".\n";
                    BB->setName(F->getName());
                    errs() << "Basic Block name: " << BB->getName() << "\n";

                    //errs() << "Total name: " << F->getName() <<"_"  ;
                    //BB->printAsOperand(errs(), false) ;
                    //BasicBlock* bb = &*BB;
                    //errs() << "\n";
                    //errs() << *bb;
                   // errs() << *BB;
                    //Instruction* ii = &*BI;
                    //errs() << *ii << "\n"; 
                   /*for (BasicBlock::iterator i = BB->begin(), e = bb->end(); i != e; ++i) {
                    Instruction* iii = &*i;
                    errs() << *iii << "\n"; }*/
                    errs() << *BB;
                    
                    Instruction *inst = &*BI;

                    errs() << "trying to insert  the instructions!\n";
                    //IRBuilder<> B(BB);
                    IRBuilder<> builder(inst);
                    //Value *v2 = B.CreateGlobalStringPtr(F->getName(), "str");
                    Value *v = builder.CreateGlobalStringPtr(BB->getName(), "str");
                    ArrayRef<Value *> args(v);
                    Instruction *newInst = CallInst::Create(monitor, args, "");
                    BB->getInstList().insert(BI, newInst); 
                    //ArrayRef<Value *> args2(v2);
                    //Instruction *newInst2 = CallInst::Create(monitor, args2, "");
                    //BB->getInstList().insert(BI, newInst2); 
                    errs() << "Inserted the instructions!\n";
                    

                
            }
        }

        return true;
    }
};
}

char SkeletonPass::ID = 0;
static RegisterPass<SkeletonPass> X("skeleton", "LLVM IR Instrumentation Pass");



