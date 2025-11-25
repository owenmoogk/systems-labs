% MATLAB script to generate the Bode plots for two transfer functions:
%
% 1. sG1(s) (from the image):
%    sG1(s) = ( (1 / (m1*m2)) * [m2*s^2 + (b2 + C)*s + k] ) / (s^3 + a1*s^2 + a2*s + a3)
%
% 2. sG2(s) (from the original script's comment, assuming the denominator is the same):
%    sG2(s) = ( (1 / (m1*m2)) * [C*s + k] ) / (s^3 + a1*s^2 + a2*s + a3)

%% 2. Calculate sG1(s) Transfer Function Coefficients
% Denominator polynomial D(s) is the same for both:
% D(s) = 1*s^3 + a1*s^2 + a2*s + a3

a1 = 118.0953;
a2 = 3.219e3;
a3 = 9.7863e3;
Denominator = [1, a1, a2, a3];

% Overall constant: 1 / (m1 * m2)
K_gain_sG1 = 1 / (m1 * m2);

% Numerator polynomial N1(s) = K_gain_sG1 * [m2*s^2 + (b2 + C)*s + k]
% Coefficients: [s^2, s^1, s^0]
num1_coeff_s2 = m2 * K_gain_sG1;
num1_coeff_s1 = (b2 + C) * K_gain_sG1;
num1_coeff_s0 = k * K_gain_sG1;
Numerator_sG1 = [num1_coeff_s2, num1_coeff_s1, num1_coeff_s0];

% Create the Transfer Function Model for sG1(s)
sys_sG1 = tf(Numerator_sG1, Denominator);
disp('The calculated transfer function sG1(s) is:');
disp(sys_sG1);

%% 3. Calculate sG2(s) Transfer Function Coefficients
% Overall constant: 1 / (m1 * m2) (same as sG1)
K_gain_sG2 = 1 / (m1 * m2);

% Numerator polynomial N2(s) = K_gain_sG2 * [C*s + k]
% Coefficients: [s^1, s^0]. Note: s^2 term is zero, so the vector is shorter.
num2_coeff_s1 = C * K_gain_sG2;
num2_coeff_s0 = k * K_gain_sG2;
Numerator_sG2 = [num2_coeff_s1, num2_coeff_s0];

% Create the Transfer Function Model for sG2(s)
sys_sG2 = tf(Numerator_sG2, Denominator);
disp(' '); % Add a blank line for separation
disp('The calculated transfer function sG2(s) is:');
disp(sys_sG2);

%% 4. Generate the Bode Plot
% Create a new figure window for the plot
figure;

% Generate the Bode plot for both systems on the same axes.
% 'bode' function automatically selects an appropriate frequency range.
bode(sys_sG1, sys_sG2);

% Add labels and grid for readability
grid on;
title('Bode Plot Comparison for sG1(s) and sG2(s)');
xlabel('Frequency (rad/s)');
ylabel('Magnitude (dB) / Phase (degrees)');

% Add a legend to distinguish the plots
legend({'sG1(s)', 'sG2(s)'}, 'Location', 'best');

% Optional: Customize magnitude label to ensure it displays 'dB'
% This section is often necessary for clean labeling in older MATLAB versions
h = findobj(gcf,'type','line');
if ~isempty(h)
    set(findall(gcf,'Tag','CSTBodeMagView'),'YLabel',{'Magnitude (dB)'});
end