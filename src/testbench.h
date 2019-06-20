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
			cout << sc_time_stamp() << "\n\n Case 1: Down Counter - ovrflw" << endl;
			reset.write(false);
			count_en.write(true);
			ud_ctrl.write(false);
			wait(2);

			cout << sc_time_stamp() << "\n\n Case 2:Resetting" << endl;
			reset.write(true);
			wait(2);

			cout << sc_time_stamp() << "\n\n Case 3:Up-counter +1" << endl;
			reset.write(false);
			count_en.write(true);
			ud_ctrl.write(true);
			wait(2);

			cout << sc_time_stamp() << "\n\n Case 4:Up-Counter +2" << endl;
			reset.write(false);
			count_en.write(true);
			ud_ctrl.write(true);
			wait(2);

			cout << sc_time_stamp() << "\n\n Case 5: Down-Counter 1" << endl;
			reset.write(false);
			count_en.write(true);
			ud_ctrl.write(false);
			wait(2);

			cout << sc_time_stamp() << "\n\n Case 6:" << endl;
			reset.write(false);
			wait(2);

			sc_stop();
		}

		SC_CTOR(Testbench){
			SC_THREAD(testbench);
			sensitive << clk.pos();
		}
};
