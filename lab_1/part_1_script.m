% Load measured data
load('4_1A.mat'); % should contain 'vout' and 'tout'

% --- First-order system parameters ---
Kv = 96.72;       % system gain
tau = 0.0237;     % time constant
Kp = 1;           % proportional gain

% --- Closed-loop first-order transfer function ---
num = Kv;
den = [tau, 1];   % first-order
sys_cl = tf(num, den);

% --- Input: square wave of amplitude 1.5 and 1 Hz ---
u = 1.5 * square(2*pi*1*tout + pi);

% --- Simulate response ---
y_theoretical = lsim(sys_cl, u, tout);

% --- Plot ---
figure;

% Define subplot layout using 'Position' for custom sizing
subplot('Position', [0.1 0.38 0.85 0.55]); % [left bottom width height]
plot(tout, vout, 'b', 'LineWidth', 1.5); hold on;
plot(tout, y_theoretical, 'r--', 'LineWidth', 1.5);
xlabel('Time (s)');
ylabel('Output Velocity (mm/s)');
title('First Order System Response to Square Wave');
legend('Measured', 'Theoretical');
grid on;

% Bottom plot (smaller)
subplot('Position', [0.1 0.1 0.85 0.2]); % smaller, 1/3 of figure height
plot(tout, u, 'k', 'LineWidth', 1.2);
xlabel('Time (s)');
ylabel('Input (V)');
title('Square Wave Input');
ylim([-2 2]); % zoomed-out y-axis
grid on;
