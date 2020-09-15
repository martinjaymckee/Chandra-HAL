



///////////////////////////////////////////////////////////////////////////////
//
//          Auto generated, optimized, Kalman Filter Implementation 
//
//
//////////////////////////////////////////////////////////////////////////////

#include <matrix.h>
#include <matrix_ops.h>

template<typename Value>
class TestKF
{
    public:
        // State Types
        using state_t = chandra::math::Matrix<Value, 9, 1>;
		using state_transition_t = chandra::math::Matrix<Value, 9, 9>;
		using state_covariance_t = chandra::math::Matrix<Value, 9, 9>;
		
		// Measurement Types
		using measurement_t = chandra::math::Matrix<Value, 4, 1>;
		using observation_model_t = chandra::math::Matrix<Value, 4, 9>;
		using measurement_covariance_t = chandra::math::Matrix<Value, 4, 4>;
		using measurement_gain_t = chandra::math::Matrix<Value, 9, 4>;
				
        TestKF() {}
        
        // NOTE: THIS TEMPLATE SHOULD USE A "STEP" TEMPLATE TO GENERATE THE 
        //   STEP FUNCTIONS, SINCE THEY ARE BASICALLY IDENTICAL
        bool init(Value dt) {
            //
            // Calculate 8 subexpressions
            //         
            x1 = dt * dt;
            x2 = Value(0.500000000000000) * x1;
            x15 = dt * dt * dt;
            x16 = Value(0.250000000000000) * (dt * dt * dt * dt);
            x19 = Value(0.500000000000000) * x15;
            x20 = Value(1.50000000000000) * x1;
            x26 = 12.0000000000000 * dt;
            x81 = 24.0000000000000 * dt;
            
            return true;
        }
        
        void predict() {
            //
            // Calculate 131 subexpressions
            // 
            x0 = X_post(1) * dt;
            x3 = X_post(2) * x2;
            x4 = X_post(2) * dt;
            x5 = 24.0000000000000 * x4;
            x6 = X_post(6) * dt;
            x7 = X_post(7) * x2;
            const Value x8 = x6 + x7;
            x9 = -1 * X_post(0);
            x10 = X_post(7) * dt;
            x11 = 24.0000000000000 * x10;
            x12 = X_post(6) + (-1 * x11);
            x13 = P(0, 1) * dt;
            x14 = P(0, 2) * x1;
            x17 = P(0, 0) + Q(0, 0) + x14 + (2 * x13) + (P(1, 1) * x1) + (P(1, 2) * x15) + (P(2, 2) * x16);
            x18 = P(0, 2) * dt;
            x21 = P(0, 1) + (P(1, 1) * dt);
            x22 = Q(0, 1) + x18 + x21 + (P(1, 2) * x20) + (P(2, 2) * x19);
            x23 = P(1, 2) * dt;
            x24 = P(2, 2) * x1;
            x25 = P(0, 2) + Q(0, 2) + x23 + (Value(0.500000000000000) * x24);
            x27 = Q(0, 3) + x21 + (P(1, 2) * x2) + (-1 * x26 * (x24 + (2 * P(0, 2)) + (2 * x23)));
            x28 = Value(0.500000000000000) * x14;
            x29 = P(0, 6) * dt;
            x30 = P(0, 7) * x1;
            x31 = x29 + (Value(0.500000000000000) * x30) + (P(1, 6) * x1) + (P(1, 7) * x19) + (P(2, 6) * x19) + (P(2, 7) * x16);
            x32 = P(0, 0) + P(0, 5) + Q(0, 4) + x13 + x28 + x31 + (P(1, 5) * dt) + (P(2, 5) * x2);
            x33 = P(0, 4) + (-1 * P(0, 0));
            x34 = Q(0, 5) + x31 + x33 + (-1 * x13) + (-1 * x28) + (P(1, 4) * dt) + (P(2, 4) * x2);
            x35 = P(0, 7) * dt;
            x36 = P(1, 6) * dt;
            x37 = P(2, 6) * x2;
            x38 = P(0, 6) + x36 + x37;
            x39 = Q(0, 6) + x35 + x38 + (P(1, 7) * x1) + (P(2, 7) * x19);
            x40 = P(1, 7) * dt;
            x41 = P(2, 7) * x1;
            x42 = Value(0.500000000000000) * x41;
            x43 = P(0, 7) + Q(0, 7) + x40 + x42;
            x44 = 2 * P(0, 7);
            x45 = x26 * (x41 + x44 + (2 * x40));
            x46 = Q(0, 8) + x38 + (-1 * x45);
            x47 = P(2, 2) * dt;
            x48 = P(1, 2) + x47;
            x49 = dt * x48;
            x50 = P(1, 1) + x23;
            x51 = Q(1, 1) + x49 + x50;
            x52 = Q(1, 2) + x48;
            x53 = Q(1, 3) + x50 + (-24.0000000000000 * x49);
            x54 = P(2, 5) * dt;
            x55 = P(2, 6) * dt;
            x56 = P(1, 6) + x55;
            x57 = P(2, 7) * dt;
            x58 = P(1, 7) + x57;
            x59 = (dt * x56) + (x2 * x58);
            x60 = P(0, 1) + P(1, 5);
            x61 = Q(1, 4) + x18 + x54 + x59 + x60;
            x62 = P(2, 4) * dt;
            x63 = P(1, 4) + (-1 * P(0, 1));
            x64 = Q(1, 5) + x59 + x62 + x63 + (-1 * x18);
            x65 = dt * x58;
            x66 = Q(1, 6) + x56 + x65;
            x67 = Q(1, 7) + x58;
            x68 = 24.0000000000000 * x65;
            x69 = Q(1, 8) + x56 + (-1 * x68);
            x70 = P(2, 2) + Q(2, 2);
            x71 = P(1, 2) + (-24.0000000000000 * x47);
            x72 = Q(2, 3) + x71;
            x73 = x42 + x55;
            x74 = P(0, 2) + P(2, 5) + Q(2, 4) + x73;
            x75 = P(2, 4) + Q(2, 5) + x73 + (-1 * P(0, 2));
            x76 = P(2, 6) + Q(2, 6) + x57;
            x77 = P(2, 7) + Q(2, 7);
            x78 = 24.0000000000000 * x57;
            x79 = -1 * x78;
            x80 = P(2, 6) + Q(2, 8) + x79;
            x82 = P(1, 1) + Q(3, 3) + (-24.0000000000000 * x23) + (-1 * x71 * x81);
            x83 = 24.0000000000000 * x18;
            x84 = 24.0000000000000 * x55;
            x85 = P(1, 6) + (-1 * x84);
            x86 = P(1, 7) + x79;
            x87 = (dt * x85) + (x2 * x86);
            x88 = Q(3, 4) + x60 + x87 + (-1 * x83) + (-24.0000000000000 * x54);
            x89 = Q(3, 5) + x63 + x83 + x87 + (-24.0000000000000 * x62);
            x90 = dt * x86;
            x91 = Q(3, 6) + x85 + x90;
            x92 = Q(3, 7) + x86;
            x93 = 24.0000000000000 * x90;
            x94 = Q(3, 8) + x85 + (-1 * x93);
            x95 = P(5, 7) * x1;
            x96 = 2 * x29;
            x97 = P(5, 6) * dt;
            x98 = (P(6, 6) * x1) + (P(6, 7) * x15) + (P(7, 7) * x16);
            x99 = P(0, 0) + x98;
            x100 = P(5, 5) + Q(4, 4) + x30 + x95 + x96 + x99 + (2 * P(0, 5)) + (2 * x97);
            x101 = P(4, 6) * dt;
            x102 = P(4, 7) * x1;
            x103 = P(4, 5) + Q(4, 5) + x101 + x33 + x97 + x98 + (Value(0.500000000000000) * x102) + (Value(0.500000000000000) * x95) + (-1 * P(0, 5));
            x104 = P(0, 6) + P(5, 6);
            x105 = P(6, 6) * dt;
            x106 = x105 + (P(6, 7) * x20) + (P(7, 7) * x19);
            x107 = Q(4, 6) + x104 + x106 + x35 + (P(5, 7) * dt);
            x108 = P(6, 7) * dt;
            x109 = P(7, 7) * x1;
            x110 = x108 + (Value(0.500000000000000) * x109);
            x111 = P(0, 7) + P(5, 7) + Q(4, 7) + x110;
            x112 = x109 + (2 * x108);
            x113 = x26 * (x112 + x44 + (2 * P(5, 7)));
            x114 = P(6, 7) * x2;
            x115 = x105 + x114;
            x116 = Q(4, 8) + x104 + x115 + (-1 * x113);
            x117 = P(4, 4) + Q(5, 5) + x102 + x99 + (-1 * x30) + (-1 * x96) + (-2 * P(0, 4)) + (2 * x101);
            x118 = -1 * P(0, 6);
            x119 = P(4, 6) + x118;
            x120 = Q(5, 6) + x106 + x119 + (-1 * x35) + (P(4, 7) * dt);
            x121 = P(4, 7) + Q(5, 7) + x110 + (-1 * P(0, 7));
            x122 = x26 * (x112 + (-1 * x44) + (2 * P(4, 7)));
            x123 = Q(5, 8) + x115 + x119 + (-1 * x122);
            x124 = P(7, 7) * dt;
            x125 = P(6, 7) + x124;
            x126 = dt * x125;
            x127 = P(6, 6) + x108;
            x128 = Q(6, 6) + x126 + x127;
            x129 = Q(6, 7) + x125;
            x130 = 24.0000000000000 * x126;
            x131 = Q(6, 8) + x127 + (-1 * x130);
            x132 = P(7, 7) + Q(7, 7);
            x133 = 24.0000000000000 * x124;
            x134 = P(6, 7) + (-1 * x133);
            x135 = Q(7, 8) + x134;
            x136 = 24.0000000000000 * x108;
            x137 = x134 * x81;
            x138 = P(6, 6) + Q(8, 8) + (-1 * x136) + (-1 * x137);
        
        }
        
        void measure() {
        }
        
    	void gain_update() {
            const Value x139 = x118 + x27 + x45 + (-1 * Q(0, 8)) + (-1 * x36) + (-1 * x37);
            const Value x140 = (-1 * x105) + (-1 * x114);
            const Value x141 = x113 + x118 + x140 + x88 + (-1 * P(5, 6)) + (-1 * Q(4, 8));
            const Value x142 = -1 * P(6, 6);
            const Value x143 = x136 + x137 + x142 + x94 + (-1 * Q(8, 8));
            const Value x144 = -1 * P(1, 6);
                	
    		return;
    	}
    
    	state_t correct() {
            const Value x145 = 1 + (-1 * K(0, 0));
            const Value x146 = K(0, 1) + (-1 * K(0, 3));
            const Value x147 = (x145 * x22) + (x146 * x69) + (-1 * K(0, 1) * x53) + (-1 * K(0, 2) * x61);
            const Value x148 = (x145 * x25) + (x146 * x80) + (-1 * K(0, 1) * x72) + (-1 * K(0, 2) * x74);
            const Value x149 = (x145 * x27) + (x146 * x94) + (-1 * K(0, 1) * x82) + (-1 * K(0, 2) * x88);
            const Value x150 = (x116 * x146) + (x145 * x32) + (-1 * K(0, 1) * x88) + (-1 * K(0, 2) * x100);
            const Value x151 = (x123 * x146) + (x145 * x34) + (-1 * K(0, 1) * x89) + (-1 * K(0, 2) * x103);
            const Value x152 = (x131 * x146) + (x145 * x39) + (-1 * K(0, 1) * x91) + (-1 * K(0, 2) * x107);
            const Value x153 = (x135 * x146) + (x145 * x43) + (-1 * K(0, 1) * x92) + (-1 * K(0, 2) * x111);
            const Value x154 = (x138 * x146) + (x145 * x46) + (-1 * K(0, 1) * x94) + (-1 * K(0, 2) * x116);
            const Value x155 = K(1, 1) + (-1 * K(1, 3));
            const Value x156 = x52 + (x155 * x80) + (-1 * K(1, 0) * x25) + (-1 * K(1, 1) * x72) + (-1 * K(1, 2) * x74);
            const Value x157 = x53 + (x155 * x94) + (-1 * K(1, 0) * x27) + (-1 * K(1, 1) * x82) + (-1 * K(1, 2) * x88);
            const Value x158 = x61 + (x116 * x155) + (-1 * K(1, 0) * x32) + (-1 * K(1, 1) * x88) + (-1 * K(1, 2) * x100);
            const Value x159 = x64 + (x123 * x155) + (-1 * K(1, 0) * x34) + (-1 * K(1, 1) * x89) + (-1 * K(1, 2) * x103);
            const Value x160 = x66 + (x131 * x155) + (-1 * K(1, 0) * x39) + (-1 * K(1, 1) * x91) + (-1 * K(1, 2) * x107);
            const Value x161 = x67 + (x135 * x155) + (-1 * K(1, 0) * x43) + (-1 * K(1, 1) * x92) + (-1 * K(1, 2) * x111);
            const Value x162 = x69 + (x138 * x155) + (-1 * K(1, 0) * x46) + (-1 * K(1, 1) * x94) + (-1 * K(1, 2) * x116);
            const Value x163 = K(2, 1) + (-1 * K(2, 3));
            const Value x164 = x72 + (x163 * x94) + (-1 * K(2, 0) * x27) + (-1 * K(2, 1) * x82) + (-1 * K(2, 2) * x88);
            const Value x165 = x74 + (x116 * x163) + (-1 * K(2, 0) * x32) + (-1 * K(2, 1) * x88) + (-1 * K(2, 2) * x100);
            const Value x166 = x75 + (x123 * x163) + (-1 * K(2, 0) * x34) + (-1 * K(2, 1) * x89) + (-1 * K(2, 2) * x103);
            const Value x167 = x76 + (x131 * x163) + (-1 * K(2, 0) * x39) + (-1 * K(2, 1) * x91) + (-1 * K(2, 2) * x107);
            const Value x168 = x77 + (x135 * x163) + (-1 * K(2, 0) * x43) + (-1 * K(2, 1) * x92) + (-1 * K(2, 2) * x111);
            const Value x169 = x80 + (x138 * x163) + (-1 * K(2, 0) * x46) + (-1 * K(2, 1) * x94) + (-1 * K(2, 2) * x116);
            const Value x170 = 1 + (-1 * K(3, 1));
            const Value x171 = K(3, 1) + (-1 * K(3, 3));
            const Value x172 = (x116 * x171) + (x170 * x88) + (-1 * K(3, 0) * x32) + (-1 * K(3, 2) * x100);
            const Value x173 = (x123 * x171) + (x170 * x89) + (-1 * K(3, 0) * x34) + (-1 * K(3, 2) * x103);
            const Value x174 = (x131 * x171) + (x170 * x91) + (-1 * K(3, 0) * x39) + (-1 * K(3, 2) * x107);
            const Value x175 = (x135 * x171) + (x170 * x92) + (-1 * K(3, 0) * x43) + (-1 * K(3, 2) * x111);
            const Value x176 = (x138 * x171) + (x170 * x94) + (-1 * K(3, 0) * x46) + (-1 * K(3, 2) * x116);
            const Value x177 = K(4, 1) + (-1 * K(4, 3));
            const Value x178 = 1 + (-1 * K(4, 2));
            const Value x179 = (x103 * x178) + (x123 * x177) + (-1 * K(4, 0) * x34) + (-1 * K(4, 1) * x89);
            const Value x180 = (x107 * x178) + (x131 * x177) + (-1 * K(4, 0) * x39) + (-1 * K(4, 1) * x91);
            const Value x181 = (x111 * x178) + (x135 * x177) + (-1 * K(4, 0) * x43) + (-1 * K(4, 1) * x92);
            const Value x182 = (x116 * x178) + (x138 * x177) + (-1 * K(4, 0) * x46) + (-1 * K(4, 1) * x94);
            const Value x183 = K(5, 1) + (-1 * K(5, 3));
            const Value x184 = x120 + (x131 * x183) + (-1 * K(5, 0) * x39) + (-1 * K(5, 1) * x91) + (-1 * K(5, 2) * x107);
            const Value x185 = x121 + (x135 * x183) + (-1 * K(5, 0) * x43) + (-1 * K(5, 1) * x92) + (-1 * K(5, 2) * x111);
            const Value x186 = x123 + (x138 * x183) + (-1 * K(5, 0) * x46) + (-1 * K(5, 1) * x94) + (-1 * K(5, 2) * x116);
            const Value x187 = K(6, 1) + (-1 * K(6, 3));
            const Value x188 = x129 + (x135 * x187) + (-1 * K(6, 0) * x43) + (-1 * K(6, 1) * x92) + (-1 * K(6, 2) * x111);
            const Value x189 = x131 + (x138 * x187) + (-1 * K(6, 0) * x46) + (-1 * K(6, 1) * x94) + (-1 * K(6, 2) * x116);
            const Value x190 = K(7, 1) + (-1 * K(7, 3));
            const Value x191 = x135 + (x138 * x190) + (-1 * K(7, 0) * x46) + (-1 * K(7, 1) * x94) + (-1 * K(7, 2) * x116);
                	
    		return this->X_post;
    	}
    
    	state_t update(const measurement_t& z, const bool& do_gain = true) {
    		predict();
    		measure(z);
    		if (do_gain) gain_update();
    		return correct();
    	}
	        
    private:
		state_t X_prior;
		state_t X_post;
		state_transition_t F;
		state_covariance_t P_prior;
		state_covariance_t P_post;
		state_covariance_t Q = state_covariance_t::Eye();
		observation_model_t H;
		measurement_covariance_t R = measurement_covariance_t::Eye();
		measurement_gain_t K;
		measurement_t y;
				
        Value x0 = 0;
        Value x1 = 0;
        Value x2 = 0;
        Value x3 = 0;
        Value x4 = 0;
        Value x5 = 0;
        Value x6 = 0;
        Value x7 = 0;
        Value x9 = 0;
        Value x10 = 0;
        Value x11 = 0;
        Value x12 = 0;
        Value x13 = 0;
        Value x14 = 0;
        Value x15 = 0;
        Value x16 = 0;
        Value x17 = 0;
        Value x18 = 0;
        Value x19 = 0;
        Value x20 = 0;
        Value x21 = 0;
        Value x22 = 0;
        Value x23 = 0;
        Value x24 = 0;
        Value x25 = 0;
        Value x26 = 0;
        Value x27 = 0;
        Value x28 = 0;
        Value x29 = 0;
        Value x30 = 0;
        Value x31 = 0;
        Value x32 = 0;
        Value x33 = 0;
        Value x34 = 0;
        Value x35 = 0;
        Value x36 = 0;
        Value x37 = 0;
        Value x38 = 0;
        Value x39 = 0;
        Value x40 = 0;
        Value x41 = 0;
        Value x42 = 0;
        Value x43 = 0;
        Value x44 = 0;
        Value x45 = 0;
        Value x46 = 0;
        Value x47 = 0;
        Value x48 = 0;
        Value x49 = 0;
        Value x50 = 0;
        Value x51 = 0;
        Value x52 = 0;
        Value x53 = 0;
        Value x54 = 0;
        Value x55 = 0;
        Value x56 = 0;
        Value x57 = 0;
        Value x58 = 0;
        Value x59 = 0;
        Value x60 = 0;
        Value x61 = 0;
        Value x62 = 0;
        Value x63 = 0;
        Value x64 = 0;
        Value x65 = 0;
        Value x66 = 0;
        Value x67 = 0;
        Value x68 = 0;
        Value x69 = 0;
        Value x70 = 0;
        Value x71 = 0;
        Value x72 = 0;
        Value x73 = 0;
        Value x74 = 0;
        Value x75 = 0;
        Value x76 = 0;
        Value x77 = 0;
        Value x78 = 0;
        Value x79 = 0;
        Value x80 = 0;
        Value x81 = 0;
        Value x82 = 0;
        Value x83 = 0;
        Value x84 = 0;
        Value x85 = 0;
        Value x86 = 0;
        Value x87 = 0;
        Value x88 = 0;
        Value x89 = 0;
        Value x90 = 0;
        Value x91 = 0;
        Value x92 = 0;
        Value x93 = 0;
        Value x94 = 0;
        Value x95 = 0;
        Value x96 = 0;
        Value x97 = 0;
        Value x98 = 0;
        Value x99 = 0;
        Value x100 = 0;
        Value x101 = 0;
        Value x102 = 0;
        Value x103 = 0;
        Value x104 = 0;
        Value x105 = 0;
        Value x106 = 0;
        Value x107 = 0;
        Value x108 = 0;
        Value x109 = 0;
        Value x110 = 0;
        Value x111 = 0;
        Value x112 = 0;
        Value x113 = 0;
        Value x114 = 0;
        Value x115 = 0;
        Value x116 = 0;
        Value x117 = 0;
        Value x118 = 0;
        Value x119 = 0;
        Value x120 = 0;
        Value x121 = 0;
        Value x122 = 0;
        Value x123 = 0;
        Value x124 = 0;
        Value x125 = 0;
        Value x126 = 0;
        Value x127 = 0;
        Value x128 = 0;
        Value x129 = 0;
        Value x130 = 0;
        Value x131 = 0;
        Value x132 = 0;
        Value x133 = 0;
        Value x134 = 0;
        Value x135 = 0;
        Value x136 = 0;
        Value x137 = 0;
        Value x138 = 0;
};


        void test_predict() {
            //
            // Calculate 131 subexpressions
            //         
            x0 = X_post(1) * dt;
            x3 = X_post(2) * x2;
            x4 = X_post(2) * dt;
            x5 = 24.0000000000000 * x4;
            x6 = X_post(6) * dt;
            x7 = X_post(7) * x2;
            const Value x8 = x6 + x7;
            x9 = -1 * X_post(0);
            x10 = X_post(7) * dt;
            x11 = 24.0000000000000 * x10;
            x12 = X_post(6) + (-1 * x11);
            x13 = P(0, 1) * dt;
            x14 = P(0, 2) * x1;
            x17 = P(0, 0) + Q(0, 0) + x14 + (2 * x13) + (P(1, 1) * x1) + (P(1, 2) * x15) + (P(2, 2) * x16);
            x18 = P(0, 2) * dt;
            x21 = P(0, 1) + (P(1, 1) * dt);
            x22 = Q(0, 1) + x18 + x21 + (P(1, 2) * x20) + (P(2, 2) * x19);
            x23 = P(1, 2) * dt;
            x24 = P(2, 2) * x1;
            x25 = P(0, 2) + Q(0, 2) + x23 + (Value(0.500000000000000) * x24);
            x27 = Q(0, 3) + x21 + (P(1, 2) * x2) + (-1 * x26 * (x24 + (2 * P(0, 2)) + (2 * x23)));
            x28 = Value(0.500000000000000) * x14;
            x29 = P(0, 6) * dt;
            x30 = P(0, 7) * x1;
            x31 = x29 + (Value(0.500000000000000) * x30) + (P(1, 6) * x1) + (P(1, 7) * x19) + (P(2, 6) * x19) + (P(2, 7) * x16);
            x32 = P(0, 0) + P(0, 5) + Q(0, 4) + x13 + x28 + x31 + (P(1, 5) * dt) + (P(2, 5) * x2);
            x33 = P(0, 4) + (-1 * P(0, 0));
            x34 = Q(0, 5) + x31 + x33 + (-1 * x13) + (-1 * x28) + (P(1, 4) * dt) + (P(2, 4) * x2);
            x35 = P(0, 7) * dt;
            x36 = P(1, 6) * dt;
            x37 = P(2, 6) * x2;
            x38 = P(0, 6) + x36 + x37;
            x39 = Q(0, 6) + x35 + x38 + (P(1, 7) * x1) + (P(2, 7) * x19);
            x40 = P(1, 7) * dt;
            x41 = P(2, 7) * x1;
            x42 = Value(0.500000000000000) * x41;
            x43 = P(0, 7) + Q(0, 7) + x40 + x42;
            x44 = 2 * P(0, 7);
            x45 = x26 * (x41 + x44 + (2 * x40));
            x46 = Q(0, 8) + x38 + (-1 * x45);
            x47 = P(2, 2) * dt;
            x48 = P(1, 2) + x47;
            x49 = dt * x48;
            x50 = P(1, 1) + x23;
            x51 = Q(1, 1) + x49 + x50;
            x52 = Q(1, 2) + x48;
            x53 = Q(1, 3) + x50 + (-24.0000000000000 * x49);
            x54 = P(2, 5) * dt;
            x55 = P(2, 6) * dt;
            x56 = P(1, 6) + x55;
            x57 = P(2, 7) * dt;
            x58 = P(1, 7) + x57;
            x59 = (dt * x56) + (x2 * x58);
            x60 = P(0, 1) + P(1, 5);
            x61 = Q(1, 4) + x18 + x54 + x59 + x60;
            x62 = P(2, 4) * dt;
            x63 = P(1, 4) + (-1 * P(0, 1));
            x64 = Q(1, 5) + x59 + x62 + x63 + (-1 * x18);
            x65 = dt * x58;
            x66 = Q(1, 6) + x56 + x65;
            x67 = Q(1, 7) + x58;
            x68 = 24.0000000000000 * x65;
            x69 = Q(1, 8) + x56 + (-1 * x68);
            x70 = P(2, 2) + Q(2, 2);
            x71 = P(1, 2) + (-24.0000000000000 * x47);
            x72 = Q(2, 3) + x71;
            x73 = x42 + x55;
            x74 = P(0, 2) + P(2, 5) + Q(2, 4) + x73;
            x75 = P(2, 4) + Q(2, 5) + x73 + (-1 * P(0, 2));
            x76 = P(2, 6) + Q(2, 6) + x57;
            x77 = P(2, 7) + Q(2, 7);
            x78 = 24.0000000000000 * x57;
            x79 = -1 * x78;
            x80 = P(2, 6) + Q(2, 8) + x79;
            x82 = P(1, 1) + Q(3, 3) + (-24.0000000000000 * x23) + (-1 * x71 * x81);
            x83 = 24.0000000000000 * x18;
            x84 = 24.0000000000000 * x55;
            x85 = P(1, 6) + (-1 * x84);
            x86 = P(1, 7) + x79;
            x87 = (dt * x85) + (x2 * x86);
            x88 = Q(3, 4) + x60 + x87 + (-1 * x83) + (-24.0000000000000 * x54);
            x89 = Q(3, 5) + x63 + x83 + x87 + (-24.0000000000000 * x62);
            x90 = dt * x86;
            x91 = Q(3, 6) + x85 + x90;
            x92 = Q(3, 7) + x86;
            x93 = 24.0000000000000 * x90;
            x94 = Q(3, 8) + x85 + (-1 * x93);
            x95 = P(5, 7) * x1;
            x96 = 2 * x29;
            x97 = P(5, 6) * dt;
            x98 = (P(6, 6) * x1) + (P(6, 7) * x15) + (P(7, 7) * x16);
            x99 = P(0, 0) + x98;
            x100 = P(5, 5) + Q(4, 4) + x30 + x95 + x96 + x99 + (2 * P(0, 5)) + (2 * x97);
            x101 = P(4, 6) * dt;
            x102 = P(4, 7) * x1;
            x103 = P(4, 5) + Q(4, 5) + x101 + x33 + x97 + x98 + (Value(0.500000000000000) * x102) + (Value(0.500000000000000) * x95) + (-1 * P(0, 5));
            x104 = P(0, 6) + P(5, 6);
            x105 = P(6, 6) * dt;
            x106 = x105 + (P(6, 7) * x20) + (P(7, 7) * x19);
            x107 = Q(4, 6) + x104 + x106 + x35 + (P(5, 7) * dt);
            x108 = P(6, 7) * dt;
            x109 = P(7, 7) * x1;
            x110 = x108 + (Value(0.500000000000000) * x109);
            x111 = P(0, 7) + P(5, 7) + Q(4, 7) + x110;
            x112 = x109 + (2 * x108);
            x113 = x26 * (x112 + x44 + (2 * P(5, 7)));
            x114 = P(6, 7) * x2;
            x115 = x105 + x114;
            x116 = Q(4, 8) + x104 + x115 + (-1 * x113);
            x117 = P(4, 4) + Q(5, 5) + x102 + x99 + (-1 * x30) + (-1 * x96) + (-2 * P(0, 4)) + (2 * x101);
            x118 = -1 * P(0, 6);
            x119 = P(4, 6) + x118;
            x120 = Q(5, 6) + x106 + x119 + (-1 * x35) + (P(4, 7) * dt);
            x121 = P(4, 7) + Q(5, 7) + x110 + (-1 * P(0, 7));
            x122 = x26 * (x112 + (-1 * x44) + (2 * P(4, 7)));
            x123 = Q(5, 8) + x115 + x119 + (-1 * x122);
            x124 = P(7, 7) * dt;
            x125 = P(6, 7) + x124;
            x126 = dt * x125;
            x127 = P(6, 6) + x108;
            x128 = Q(6, 6) + x126 + x127;
            x129 = Q(6, 7) + x125;
            x130 = 24.0000000000000 * x126;
            x131 = Q(6, 8) + x127 + (-1 * x130);
            x132 = P(7, 7) + Q(7, 7);
            x133 = 24.0000000000000 * x124;
            x134 = P(6, 7) + (-1 * x133);
            x135 = Q(7, 8) + x134;
            x136 = 24.0000000000000 * x108;
            x137 = x134 * x81;
            x138 = P(6, 6) + Q(8, 8) + (-1 * x136) + (-1 * x137);
            
            //
            // Calculate Matrix Values
            //
            
            return;
        }

