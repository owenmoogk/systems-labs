% Load experimental data
data1 = load('2_1a.mat');
data2 = load('2_1b.mat');

% Define plant parameters
m = 2.45e-4;      % mass [kg]
b = 0.010339;     % damping coefficient [N*s/m]

% Define PD controller gains
Kp = 3947.86 * m;     % proportional gain
Kd = 0.008134;    % derivative gain

% Create Laplace variable
s = tf('s');

% Closed-loop PD-controlled plant
plant = 1/(s*(m*s + b));
controller = Kp + Kd*s;
sys = feedback(controller*plant, 1);  % unity negative feedback

% Original time vectors
t1 = data1.time;
t2 = data2.time;

% Reference signals
x_r1 = data1.x_r;
x_r2 = data2.x_r;

% --- Resample input to avoid undersampling ---
dt = 1e-4;  % smaller than 2.4e-4 as suggested by warning

t1_fine = t1(1):dt:t1(end);
x_r1_fine = interp1(t1, x_r1, t1_fine, 'linear');

t2_fine = t2(1):dt:t2(end);
x_r2_fine = interp1(t2, x_r2, t2_fine, 'linear');

% Simulate responses
y_sim1 = lsim(sys, x_r1_fine, t1_fine);
y_sim2 = lsim(sys, x_r2_fine, t2_fine);

% --- Plot 2_1a ---
figure;
plot(t1, x_r1, 'Color', [0.6 0.6 0.6], 'LineWidth', 1); hold on;
plot(t1, data1.x_out, 'b', 'LineWidth', 1.2);
plot(t1_fine, y_sim1, 'r--', 'LineWidth', 1.2);
title('2\_1a Response: Experimental vs Simulated');
xlabel('Time (s)');
ylabel('Position (mm)');
legend('Reference', 'Experimental', 'Simulated');
grid on;

% --- Plot 2_1b ---
figure;
plot(t2, x_r2, 'Color', [0.6 0.6 0.6], 'LineWidth', 1); hold on;
plot(t2, data2.x_out, 'b', 'LineWidth', 1.2);
plot(t2_fine, y_sim2, 'r--', 'LineWidth', 1.2);
title('2\_1b Response: Experimental vs Simulated');
xlabel('Time (s)');
ylabel('Position (mm)');
legend('Reference', 'Experimental', 'Simulated');
grid on;
