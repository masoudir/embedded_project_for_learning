duty cycle[%] = CCRX / ARRX [%]

F(pwm) = F(clk) / (ARR +1)*(PSC+1)

Resolution = this parameter determines that how many seteps should DUTYCYCLE from 0 till max take.
Resolution(pwm) = log(F(clk)/F(pwm)) / log(2)  