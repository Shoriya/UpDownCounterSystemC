#include "UpDownCounter.h"
#include "testbench.h"

int sc_main(int argc, char * argv[]) {

	sc_signal<int> sig;
	Counter* udcounter = new Counter("udcounter");
	Testbench* countertb = new Testbench("countertb");

	sc_clock Clock("Clock", 10, SC_NS, 0.5, 10, SC_NS, false);

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

	cout<< "Start simulation" <<endl;
	sc_start(10, SC_SEC);
	return 0;
}
