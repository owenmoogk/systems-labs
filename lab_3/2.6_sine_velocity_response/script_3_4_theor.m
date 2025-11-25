% MATLAB script to generate the Bode plot for the given transfer function.
%
% H(s) = sG_2(s) = ( (1/(m1*m2)) * (Cs + k) ) / (s^3 + a1*s^2 + a2*s + a3)

%% 1. Define Constants
% Replace these placeholder values with your actual system parameters.
% Ensure all variables are defined as real, non-zero numbers where appropriate.

%% 2. Calculate Numerator and Denominator Coefficients

% The overall constant multiplying the numerator term (1 / (m1*m2))
K_gain = 1 / (m1 * m2);

% Numerator polynomial N(s) = (C * K_gain) * s + (k * K_gain)
% The coefficients are ordered by descending power of s: [s^1, s^0]
num_coeff_s1 = C * K_gain;
num_coeff_s0 = k * K_gain;
Numerator = [num_coeff_s1, num_coeff_s0];

% Denominator polynomial D(s) = 1*s^3 + a1*s^2 + a2*s + a3
% The coefficients are ordered by descending power of s: [s^3, s^2, s^1, s^0]
Denominator = [1, a1, a2, a3];


%% 3. Create the Transfer Function Model

% Create the system model using the 'tf' function (Transfer Function)
sys = tf(Numerator, Denominator);

% Display the system model in the command window for verification
disp('The calculated transfer function sG_2(s) is:');
disp(sys);


%% 4. Generate the Bode Plot

% Create a new figure window for the plot
figure;

% Generate the Bode plot (Magnitude and Phase vs. Frequency)
% The 'bode' function automatically selects an appropriate frequency range.
bode(sys);

% Add labels and grid for readability
grid on;
title('Bode Plot of Transfer Function sG_2(s)');
xlabel('Frequency (rad/s)');

% Optional: Set the magnitude units to dB
h = findobj(gcf,'type','line');
if ~isempty(h)
    set(findall(gcf,'Tag','CSTBodeMagView'),'YLabel',{'Magnitude (dB)'});
end

% Optional: Set specific frequency limits if needed (uncomment to use)
% w = logspace(-2, 3, 500); % Example: 500 points from 0.01 to 1000 rad/s
% figure;
% bode(sys, w);