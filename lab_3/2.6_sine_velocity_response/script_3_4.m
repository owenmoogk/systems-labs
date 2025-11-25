% MATLAB script to generate the Bode plots for two transfer functions:
%
% 1. sG1(s): Magnitude on a logarithmic gain scale.
% 2. sG2(s): Magnitude on a logarithmic gain scale.
%
% The phase plot remains in degrees on a linear scale.

%% 1. Define Constants
% Replace these placeholder values with your actual system parameters.
% Ensure all variables are defined as real, non-zero numbers where appropriate.

% Denominator Coefficients
a1 = 10;
a2 = 50;
a3 = 100;

% System Mass/Inertia
m1 = 1;
m2 = 0.5;

% System Damping/Friction and Stiffness
b2 = 0.1; % Damping coefficient (e.g., in sG1)
C = 0.2;  % Damping coefficient (e.g., in sG2 and sG1)
k = 10;   % Stiffness coefficient

%% 2. Calculate sG1(s) Transfer Function Coefficients and Model
Denominator = [1, a1, a2, a3];
K_gain_sG1 = 1 / (m1 * m2);
num1_coeff_s2 = m2 * K_gain_sG1;
num1_coeff_s1 = (b2 + C) * K_gain_sG1;
num1_coeff_s0 = k * K_gain_sG1;
Numerator_sG1 = [num1_coeff_s2, num1_coeff_s1, num1_coeff_s0];
sys_sG1 = tf(Numerator_sG1, Denominator);

%% 3. Calculate sG2(s) Transfer Function Coefficients and Model
K_gain_sG2 = 1 / (m1 * m2);
num2_coeff_s1 = C * K_gain_sG2;
num2_coeff_s0 = k * K_gain_sG2;
Numerator_sG2 = [num2_coeff_s1, num2_coeff_s0];
sys_sG2 = tf(Numerator_sG2, Denominator);

%% 4. Generate the Plot Data 💾
% Define a standard frequency range (w) to evaluate the response
w = logspace(-1, 3, 200);

% Calculate the frequency response (complex numbers) for both systems
[mag1, phase1] = bode(sys_sG1, w);
[mag2, phase2] = bode(sys_sG2, w);

% The bode function output 'mag' is already the linear gain value |G(jw)|.
% The output arrays 'mag1' and 'mag2' are 1x1xN arrays, so we must reshape them.
mag1 = reshape(mag1, numel(mag1), 1);
phase1 = reshape(phase1, numel(phase1), 1);
mag2 = reshape(mag2, numel(mag2), 1);
phase2 = reshape(phase2, numel(phase2), 1);

%% 5. Generate the Logarithmic Gain Magnitude Plot 📈
figure;

% --- Magnitude Plot (Log-Log Scale for Gain) ---
subplot(2, 1, 1); % Top plot for Magnitude
loglog(w, mag1, 'b', 'LineWidth', 1.5);
hold on;
loglog(w, mag2, 'r--', 'LineWidth', 1.5);
hold off;

grid on;
title('Magnitude Plot (Linear Gain on Logarithmic Scale)');
% Note: The y-axis is labeled as Gain, but is log-scaled by the loglog function.
ylabel('Gain |G(j\omega)| (Linear Scale)');
legend({'sG1(s)', 'sG2(s)'}, 'Location', 'best');

% --- Phase Plot (Standard Bode Plot Phase) ---
subplot(2, 1, 2); % Bottom plot for Phase
semilogx(w, phase1, 'b', 'LineWidth', 1.5);
hold on;
semilogx(w, phase2, 'r--', 'LineWidth', 1.5);
hold off;

grid on;
title('Phase Plot');
xlabel('Frequency (rad/s)');
ylabel('Phase (degrees)');