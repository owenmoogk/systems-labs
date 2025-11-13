% Load experimental data
data1 = load('2_1a.mat');
data2 = load('2_1b.mat');

% Load simulated data from Simulink (contains 'out' object)
sim1_data = load('3_1a_2_1a.mat');  % contains 'out'
sim2_data = load('3_1a_2_1b.mat');  % contains 'out'

% --- Extract signals from the out object and convert to numeric arrays ---
% For sim1
sim1_time  = double(sim1_data.out.get('tout'));  % simulation time
sim1_x_out = double(sim1_data.out.get('x_sim').Data);  % simulated position
sim1_u     = double(sim1_data.out.get('u_sim').Data);  % control signal

% For sim2
sim2_time  = double(sim2_data.out.get('tout'));
sim2_x_out = double(sim2_data.out.get('x_sim').Data);
sim2_u     = double(sim2_data.out.get('u_sim').Data);

% --- Interpolate simulated outputs to experimental time ---
sim1_x_interp = interp1(sim1_time, sim1_x_out, data1.time, 'linear');
sim2_x_interp = interp1(sim2_time, sim2_x_out, data2.time, 'linear');

% --- Compute tracking errors ---
err1 = data1.x_r - sim1_x_interp;
err2 = data2.x_r - sim2_x_interp;

% --- Plot 2_1a ---
figure;

% 1: System response
subplot(3,1,1);
plot(data1.time, data1.x_r, 'Color', [0.6 0.6 0.6], 'LineWidth', 1); hold on;
plot(data1.time, data1.x_out, 'b', 'LineWidth', 1.2);
plot(data1.time, sim1_x_interp, 'r--', 'LineWidth', 1.2);
title('2\_1a: Position Response');
ylabel('Position (mm)');
legend('Reference', 'Experimental', 'Simulated');
grid on;

% 2: Tracking error
subplot(3,1,2);
plot(data1.time, err1, 'k', 'LineWidth', 1.2);
title('Tracking Error (x_r - x_{out})');
ylabel('Error (mm)');
grid on;

% 3: Control signal
subplot(3,1,3);
plot(sim1_time, sim1_u, 'm', 'LineWidth', 1.2);
title('Control Signal u(t)');
xlabel('Time (s)');
ylabel('u(t)');
grid on;

% --- Plot 2_1b ---
figure;

% 1: System response
subplot(3,1,1);
plot(data2.time, data2.x_r, 'Color', [0.6 0.6 0.6], 'LineWidth', 1); hold on;
plot(data2.time, data2.x_out, 'b', 'LineWidth', 1.2);
plot(data2.time, sim2_x_interp, 'r--', 'LineWidth', 1.2);
title('2\_1b: Position Response');
ylabel('Position (mm)');
legend('Reference', 'Experimental', 'Simulated');
grid on;

% 2: Tracking error
subplot(3,1,2);
plot(data2.time, err2, 'k', 'LineWidth', 1.2);
title('Tracking Error (x_r - x_{out})');
ylabel('Error (mm)');
grid on;

% 3: Control signal
subplot(3,1,3);
plot(sim2_time, sim2_u, 'm', 'LineWidth', 1.2);
title('Control Signal u(t)');
xlabel('Time (s)');
ylabel('u(t)');
grid on;
