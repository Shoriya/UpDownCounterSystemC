#include<systemc.h>

SC_MODULE(Counter){
	//inputs
	sc_in<bool> reset;
	sc_in<bool> count_en;
	sc_in<bool> ud_ctrl;
	sc_in<bool> clk;

	//outputs
	sc_out<sc_bv<17> > count_out;
	sc_out<bool> ovf_intr;
	sc_out<bool> unf_intr;

	//variables
	sc_uint<17> count;



	void UpDowncounter()
	{
		if(reset.read()==true){
			cout<<"Reseting:\n";
			count=0;
			count_out.write(count);
			ovf_intr.write(false);
			unf_intr.write(false);
		}
		else{
			if(count_en.read()==true){
				if(ud_ctrl.read()==true){
					count = (count+1);
					cout << "Up Counter: \n";
					count_out.write(count);
					ovf_intr.write(count == 0 ? true :false);
					unf_intr.write(false);
				}
				else{
					count = (count-1);
					cout << "Down Counter: \n";
					count_out.write(count);
					ovf_intr.write(false);
					unf_intr.write(count == (1<<17)-1 ? true : false);

				}

			}
		}
		count_out = count;
		cout << sc_time_stamp();
		cout <<"Count:" << count <<"\n";
		cout <<"Count:" << count_out <<"\n";
		cout <<"Overflow:"<< ovf_intr << "\n";
		cout <<"Underflow:"<< unf_intr << "\n";
	}

	SC_CTOR(Counter){
			SC_METHOD(UpDowncounter);
			sensitive << clk.pos();
		}

};
