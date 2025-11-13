% Load experimental data
data1 = load('2_1a.mat');  % contains time, x_r, x_out, u
data2 = load('2_1b.mat');

% Load simulated data from Simulink (contains 'out' object)
sim1_data = load('3_1a_2_1a.mat');  % contains 'out'
sim2_data = load('3_1a_2_1b.mat');  % contains 'out'

% --- Extract signals from the out object ---
sim1_time  = double(sim1_data.out.get('tout'));
sim1_x_out = double(sim1_data.out.get('x_sim').Data);
sim1_u     = double(sim1_data.out.get('u_sim').Data);

sim2_time  = double(sim2_data.out.get('tout'));
sim2_x_out = double(sim2_data.out.get('x_sim').Data);
sim2_u     = double(sim2_data.out.get('u_sim').Data);

% --- Interpolate simulated outputs to experimental time ---
sim1_x_interp = interp1(sim1_time, sim1_x_out, data1.time, 'linear');
sim2_x_interp = interp1(sim2_time, sim2_x_out, data2.time, 'linear');

% --- Compute tracking errors ---
err1_exp = data1.x_r - data1.x_out;
err1_sim = data1.x_r - sim1_x_interp;

err2_exp = data2.x_r - data2.x_out;
err2_sim = data2.x_r - sim2_x_interp;

% --- Plot 2_1a ---
figure;

% 1: System response
subplot(3,1,1);
plot(data1.time, data1.x_r, 'Color', [0.6 0.6 0.6], 'LineWidth', 1); hold on;
plot(data1.time, data1.x_out, 'b', 'LineWidth', 1.2);
plot(data1.time, sim1_x_interp, 'r--', 'LineWidth', 1.2);
title('Position Response');
ylabel('Position (mm)');
legend('Reference', 'Experimental', 'Simulated');
grid on;

% 2: Tracking error
subplot(3,1,2);
plot(data1.time, err1_exp, 'b', 'LineWidth', 1.2); hold on;
plot(data1.time, err1_sim, 'r--', 'LineWidth', 1.2);
title('Tracking Error');
ylabel('Error (mm)');
legend('Experimental', 'Simulated');
grid on;

% 3: Control signal
subplot(3,1,3);
plot(data1.time, data1.u, 'b', 'LineWidth', 1.2); hold on;
plot(sim1_time, sim1_u, 'r--', 'LineWidth', 1.2);
title('Control Signal');
xlabel('Time (s)');
ylabel('u(t)');
legend('Experimental', 'Simulated');
grid on;

% --- Plot 2_1b ---
figure;

% 1: System response
subplot(3,1,1);
plot(data2.time, data2.x_r, 'Color', [0.6 0.6 0.6], 'LineWidth', 1); hold on;
plot(data2.time, data2.x_out, 'b', 'LineWidth', 1.2);
plot(data2.time, sim2_x_interp, 'r--', 'LineWidth', 1.2);
title('Position Response');
ylabel('Position (mm)');
legend('Reference', 'Experimental', 'Simulated');
grid on;

% 2: Tracking error
subplot(3,1,2);
plot(data2.time, err2_exp, 'b', 'LineWidth', 1.2); hold on;
plot(data2.time, err2_sim, 'r--', 'LineWidth', 1.2);
title('Tracking Error');
ylabel('Error (mm)');
legend('Experimental', 'Simulated');
grid on;

% 3: Control signal
subplot(3,1,3);
plot(data2.time, data2.u, 'b', 'LineWidth', 1.2); hold on;
plot(sim2_time, sim2_u, 'r--', 'LineWidth', 1.2);
title('Control Signal');
xlabel('Time (s)');
ylabel('u(t)');
legend('Experimental', 'Simulated');
grid on;
