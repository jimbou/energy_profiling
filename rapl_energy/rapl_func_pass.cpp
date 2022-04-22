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
    Function *monitorbb;    // this will be the identifier for the print function
    Function *monitorfunc;    // this will be the identifier for the print function
    Function *raplread;   // this will be the identifier for the rapl read function

    SkeletonPass() : ModulePass(ID) {}

    virtual bool runOnModule(Module &M)
    {

        for(Module::iterator F = M.begin(), E = M.end(); F!= E; ++F)
        {
            if(F->getName() == "printbb"){
                monitorbb = cast<Function>(F);  // cast the print function to the monitor pointer
                continue;
            }
            
            if(F->getName() == "printfunc"){
                monitorfunc = cast<Function>(F);  // cast the print function to the monitor pointer
                continue;
            }

            if(F->getName() == "readrapl"){
                raplread = cast<Function>(F);  // cast the readrapl function to the raplread pointer
                continue;
            }
            Function::iterator FI = F->begin();
            Function::iterator FF = F->end();
            FF--;
            BasicBlock::iterator FBI = FI->begin(); 

            Instruction *instn = &*FBI;
            IRBuilder<> builder1(instn);
            Value *v = builder1.CreateGlobalStringPtr(F->getName(), "str");
            ArrayRef<Value *> args(v);
            Instruction *newInstn = CallInst::Create(monitorfunc, args, "");    // create the first insttruction to be added : a call to the print function
            FI->getInstList().insert(FBI, newInstn); 

            Instruction *newInst3 = CallInst::Create(raplread, "");      //create the second instruction to be added : a call to the readrapl function which reads rapl energy
            FI->getInstList().insert(FBI, newInst3); 
            FF->getInstList().push_back(newInst3); 
             

            for(Function::iterator BB = F->begin(), E = F->end(); BB != E; ++BB)
            {
               
                    BasicBlock::iterator BI = BB->begin();     // BI will hold the begging point  of the basic block so that we can insert instructions there
                    BasicBlock::iterator BF = BB->end();
                    BF--;                                      // BF will hold the ending point  of the basic block so that we can insert instructions there
                   
                    errs() << "new basic block\n";
                    BB->setName(F->getName());                // set the name of the bb to its function name plus a unique number which will be added automatically . for more check read.ME
                   
                    errs() << "Basic Block name: " << BB->getName() << "\n";  // print the name of the current BB
                    errs() << *BB;                                            // print the contents of the bb in the form of llvm IR assembly instructions
                    
                    Instruction *inst = &*BI;
                    IRBuilder<> builder(inst);
                    Value *v = builder.CreateGlobalStringPtr(BB->getName(), "str");
                    ArrayRef<Value *> args(v);
                    Instruction *newInst = CallInst::Create(monitorbb, args, "");    // create the first insttruction to be added : a call to the print function
                    BB->getInstList().insert(BI, newInst);                         // we give as argument the name of the bb and we insert it at the beggining f the bb
              
                  /*
              
                    Instruction *newInst0 = CallInst::Create(raplread, "");      //create the second instruction to be added : a call to the readrapl function which reads rapl energy
                    BB->getInstList().insert(BI, newInst0);                       // we insert it at the beggining of the basic block and it will print two energy values
              
                    Instruction *newInst1 = CallInst::Create(raplread, "");     //create the third instruction to be added : a call to the readrapl function which reads rapl energy
                    BB->getInstList().push_back(newInst1);                     // we insert it at the end of the basic block and it will print two energy values
                      */                 

                
            }
        }

        return true;
    }
};
}

char SkeletonPass::ID = 0;
static RegisterPass<SkeletonPass> X("skeleton", "LLVM IR Instrumentation Pass");


