#include "UpDownCounter.h"
#include "testbench.h"

int sc_main(int argc, char * argv[]) {

	sc_signal<int> sig;
	Testbench* countertb = new Testbench("countertb");
	Counter* udcounter = new Counter("udcounter");


	sc_clock Clock("Clock", 20, SC_NS, 0.5, 0, SC_NS, false);

	sc_signal<bool> reset;
	sc_signal<bool> count_en;
	sc_signal<bool> ud_ctrl;
    sc_signal<sc_bv<17> > count_out;
	sc_signal<bool> ovf_intr;
	sc_signal<bool> unf_intr;

	udcounter->clk(Clock);
	udcounter->reset(reset);
	udcounter->count_en(count_en);
	udcounter->ud_ctrl(ud_ctrl);
	udcounter->count_out(count_out);
	udcounter->ovf_intr(ovf_intr);
	udcounter->unf_intr(unf_intr);

	countertb->clk(Clock);
	countertb->reset(reset);
	countertb->count_en(count_en);
	countertb->ud_ctrl(ud_ctrl);
	countertb->count_out(count_out);
	countertb->ovf_intr(ovf_intr);
	countertb->unf_intr(unf_intr);

	cout<< sc_time_stamp() <<"Creating VCD file:\n";
	sc_trace_file* file = sc_create_vcd_trace_file("UpDownCounter");

	sc_trace(file,Clock,"clock");
	sc_trace(file,reset,"reset");
	sc_trace(file,count_en,"count_en");
	sc_trace(file,ud_ctrl,"ud_ctrl");
	sc_trace(file,count_out,"count_out");
	sc_trace(file,ovf_intr,"ovf_intr");
	sc_trace(file,unf_intr,"unf_intr");

	cout<< "Start Simulation" <<endl;
	sc_start();
	return 0;
}
