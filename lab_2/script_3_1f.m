% Load experimental data
data = load('2_1b.mat');  % contains time, x_r, x_out, u

% Load simulated data from Simulink (contains 'out' object)
sim_data = load('3_1f.mat');  % contains 'out'

% --- Extract signals from the out object ---
sim_time  = double(sim_data.out.get('tout'));
sim_x_out = double(sim_data.out.get('x_sim').Data);
sim_u     = double(sim_data.out.get('u_sim').Data);

% --- Interpolate simulated outputs to experimental time ---
sim_x_interp = interp1(sim_time, sim_x_out, data.time, 'linear');

% --- Compute tracking errors ---
err_exp = data.x_r - data.x_out;
err_sim = data.x_r - sim_x_interp;

% --- Plot 2_1b ---
figure;

% 1: System response
subplot(3,1,1);
plot(data.time, data.x_r, 'Color', [0.6 0.6 0.6], 'LineWidth', 1); hold on;
plot(data.time, data.x_out, 'b', 'LineWidth', 1.2);
plot(data.time, sim_x_interp, 'r--', 'LineWidth', 1.2);
title('Position Response');
ylabel('Position (mm)');
legend('Reference', 'Experimental', 'Simulated');
grid on;

% 2: Tracking error
subplot(3,1,2);
plot(data.time, err_exp, 'b', 'LineWidth', 1.2); hold on;
plot(data.time, err_sim, 'r--', 'LineWidth', 1.2);
title('Tracking Error');
ylabel('Error (mm)');
legend('Experimental', 'Simulated');
grid on;

% 3: Control signal
subplot(3,1,3);
plot(data.time, data.u, 'b', 'LineWidth', 1.2); hold on;
plot(sim_time, sim_u, 'r--', 'LineWidth', 1.2);
title('Control Signal');
xlabel('Time (s)');
ylabel('u(t)');
legend('Experimental', 'Simulated');
grid on;
