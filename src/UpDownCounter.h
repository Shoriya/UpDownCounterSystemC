#include<systemc.h>
#include<math.h>

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
					cout << "Up Counter: \n";
					if(count == (pow(2,17)-1))
					{
						ovf_intr.write(true);
						count=0;
					}
					else
					{
						count +=1;
						ovf_intr.write(false);
					}
					count_out.write(count);
				}
				else{
					cout << "Down Counter: \n";
					if(count==0)
					{
						unf_intr.write(true);
						count = (pow(2,17)-1);
					}
					else
					{
						count -= 1;
						unf_intr.write(false);
					}
					count_out.write(count);
				}

			}
		}

		cout << "\n\n" << sc_time_stamp();
		cout <<"Count:" << count <<"\n";
		cout <<"Count:" << count_out <<"\n";
		cout <<"Overflow:"<< ovf_intr << "\n";
		cout <<"Underflow:"<< unf_intr << "\n";
	}

	SC_CTOR(Counter){
			SC_METHOD(UpDowncounter);
			sensitive << clk.neg();
	}

};
