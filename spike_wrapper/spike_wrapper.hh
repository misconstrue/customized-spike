#ifndef __SPIKE_WRAPPER_H__
#define __SPIKE_WRAPPER_H__

class SpikeWrapper: public sim_t {
public:    
    SpikeWrapper();
    ~SpikeWrapper();

    // sim->mmio_load  sim->mmio_store
    bool read_mem(reg_t paddr, size_t len, uint8_t* bytes);
    bool write_mem(reg_t paddr, size_t len, const uint8_t* bytes);
    // processor put/get csr
    void write_csr(int which, reg_t val);
    reg_t read_csr(int which);
    // XPR FPR VU
    reg_t get_x_reg();
    reg_t get_f_reg();
    

    // start_pc:modify state pc in processor
    // count:
    void run(reg_t start_pc, size_t count);
    void reset();
};



#endif