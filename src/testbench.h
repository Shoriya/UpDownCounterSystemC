#include<systemc.h>

SC_MODULE(Testbench){
	//inputs
		sc_out<bool> reset;
		sc_out<bool> count_en;
		sc_out<bool> ud_ctrl;
		sc_in<bool> clk;

		//outputs
		sc_in<sc_bv<17> > count_out;
		sc_in<bool> ovf_intr;
		sc_in<bool> unf_intr;

		void testbench(){
			cout<< sc_time_stamp() <<"Creating VCD file:\n";
			sc_trace_file* file = sc_create_vcd_trace_file("UpDownCounter");
			sc_trace(file,clk,"clock");
			sc_trace(file,reset,"reset");
			sc_trace(file,count_en,"count_en");
			sc_trace(file,ud_ctrl,"ud_ctrl");
			sc_trace(file,count_out,"count_out");
			sc_trace(file,ovf_intr,"ovf_intr");
			sc_trace(file,unf_intr,"unf_intr");

			cout << sc_time_stamp() << "Case1: Setting Reset to 1" << endl;
			reset.write(true);
			wait(1);

			cout << sc_time_stamp() << "Case 2: Setting Reset to 0 and Up/Down Control to 0 (Decrement)" << endl;
			reset.write(false);
			count_en.write(false);
			ud_ctrl.write(false);
			wait(3);

			cout << sc_time_stamp() << " Setting Counter Enable to 1" << endl;
			count_en.write(true);
			wait(5);

			cout << "@" << sc_time_stamp() << " Setting Up/Down Control to 1 (Increment)" << endl;
			ud_ctrl.write(true);
			wait(20);

//			cout << "@" << sc_time_stamp() << " Setting Reset to 1" << endl;
//			reset.write(true);
//			wait(2);

//			cout << "@" << sc_time_stamp() << " Setting Reset to 0" << endl;
//			reset.write(false);
//			wait(50);
			sc_stop();
		}

		SC_CTOR(Testbench){
			SC_THREAD(testbench);
			sensitive << clk;
		}
};
