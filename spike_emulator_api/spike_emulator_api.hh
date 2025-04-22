#ifndef __SPIKE_EMULATOR_API_H__
#define __SPIKE_EMULATOR_API_H__

#include "config.h"
#include "cfg.h"
#include "sim.h"
#include "mmu.h"
#include "arith.h"
#include "remote_bitbang.h"
#include "cachesim.h"
#include "extension.h"
#include <dlfcn.h>
#include <fesvr/option_parser.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <limits>
#include <cinttypes>
#include <sstream>
#include "../VERSION"
#include "decode.h"

#define MAX_ARGS_LEN 1000
#define MAX_ARGS 100
//   int r = std::find(fpr_name, fpr_name + NFPR, args[1]) - fpr_name;
class SpikeEmulator {
public:
    SpikeEmulator(const char *filename);
    ~SpikeEmulator();

    // sim->mmio_load  sim->mmio_store
    bool mmio_load(reg_t paddr, size_t len, uint8_t* bytes);
    bool mmio_store(reg_t paddr, size_t len, const uint8_t* bytes);
    // get_core->get_state->XPR/XPR.write(size_t i, T value)
    // get_core->get_state->FPR/FPR.wirte(size_t i, T value)
    // get_core->get_state->VU.reg_file
    // #define DECLARE_CSR(name, number) if (args[1] == #name) return p->get_csr(number);
    // #include "encoding.h"
    void reg_write(std::string name, const void *value);
    void reg_read(std::string name, void *value);
    // start_pc:modify state pc in processor
    // count: step(n)
    void run(reg_t start_pc, size_t count);
    // delete sim_t and call init_spike_env again 
    void reset();
    int init_spike_env(int argc, char ** argv);


private:
    // 命令行参数需要记录下来，以便之后复位状态使用
    char **argv;
    int argc;
    std::shared_ptr<sim_t> s;
    std::vector<std::pair<reg_t, abstract_mem_t*> > mems;
};

#endif