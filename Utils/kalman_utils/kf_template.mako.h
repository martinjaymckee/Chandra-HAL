<%!
import kalman_utils.kf_reports as kfr 
expr_fmt = kfr.CppGenerator(matrix_symbols=['X_pre', 'X_post', 'F', 'H', 'P', 'Q', 'R', 'K'])
%>

<%def name="step_render(name, subexprs, matricies=[], params=[], result=None)">
        ${'void' if result is None else result[0]} ${name}(${', '.join(params)}) {
            //
            // Calculate ${len(subexprs)} subexpressions
            //         
            % for variable in subexprs:
            ${'' if variable[0] else 'const Value '}${variable[1]} = ${expr_fmt.format(variable[2])};
            % endfor            
            
            //
            // Calculate Matrix Values
            //
            
            return${'' if result is None else result[1]};
        }
</%def>

///////////////////////////////////////////////////////////////////////////////
//
//          Auto generated, optimized, Kalman Filter Implementation 
//
//
//////////////////////////////////////////////////////////////////////////////

#include <matrix.h>
#include <matrix_ops.h>

template<typename Value>
class ${kf_class_name}
{
    public:
        // State Types
        using state_t = chandra::math::Matrix<Value, ${state_size}, 1>;
		using state_transition_t = chandra::math::Matrix<Value, ${state_size}, ${state_size}>;
		using state_covariance_t = chandra::math::Matrix<Value, ${state_size}, ${state_size}>;
		
		// Measurement Types
		using measurement_t = chandra::math::Matrix<Value, ${measurement_size}, 1>;
		using observation_model_t = chandra::math::Matrix<Value, ${measurement_size}, ${state_size}>;
		using measurement_covariance_t = chandra::math::Matrix<Value, ${measurement_size}, ${measurement_size}>;
		using measurement_gain_t = chandra::math::Matrix<Value, ${state_size}, ${measurement_size}>;
				
        ${kf_class_name}() {}
        
        // NOTE: THIS TEMPLATE SHOULD USE A "STEP" TEMPLATE TO GENERATE THE 
        //   STEP FUNCTIONS, SINCE THEY ARE BASICALLY IDENTICAL
        bool init(${', '.join(['Value {}'.format(p.name) for p in init_params if not p.calc])}) {
            //
            // Calculate ${len(init_subexprs)} subexpressions
            //         
            % for variable in init_subexprs:
            ${'' if variable[0] else 'const Value '}${variable[1]} = ${expr_fmt.format(variable[2])};
            % endfor
            
            return true;
        }
        
        void predict() {
            //
            // Calculate ${len(predict_subexprs)} subexpressions
            // 
            % for variable in predict_subexprs:
            ${'' if variable[0] else 'const Value '}${variable[1]} = ${expr_fmt.format(variable[2])};
            % endfor         
        
        }
        
        void measure() {
            % for variable in measure_subexprs:
            ${'' if variable[0] else 'const Value '}${variable[1]} = ${expr_fmt.format(variable[2])};
            % endfor                 
        }
        
    	void gain_update() {
            % for variable in gain_update_subexprs:
            ${'' if variable[0] else 'const Value '}${variable[1]} = ${expr_fmt.format(variable[2])};
            % endfor         
                	
    		return;
    	}
    
    	state_t correct() {
            % for variable in correct_subexprs:
            ${'' if variable[0] else 'const Value '}${variable[1]} = ${expr_fmt.format(variable[2])};
            % endfor         
                	
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
				
        % for variable in member_vars:
        Value ${variable[0]} = 0;
        % endfor    
};

${step_render('test_predict', predict_subexprs)}
