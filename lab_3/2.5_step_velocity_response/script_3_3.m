%% --- File list ---
files_15v = {"2_5_15_01.mat", "2_5_15_02.mat", "2_5_15_03.mat"};

%% --- Load experimental data ---
load_trials = @(flist) cellfun(@(f) load(f), flist, 'UniformOutput', false);
data_15v = load_trials(files_15v);

%% --- Load simulation data ---
sim_data = load('3_3_sim.mat');  % contains v1_sim, v2_sim arrays

%% --- Extractors ---
get_time  = @(d) d.ScopeData_v1_fit.time(:);  
get_v1    = @(d) d.ScopeData_v1_fit.signals.values(:);
get_v2    = @(d) d.ScopeData_v2_fit.signals.values(:);

%% ========== 1.5 V EXPERIMENT ==========
t_exp = get_time(data_15v{1});

v1_exp = [ get_v1(data_15v{1}), ...
           get_v1(data_15v{2}), ...
           get_v1(data_15v{3}) ];

v2_exp = [ get_v2(data_15v{1}), ...
           get_v2(data_15v{2}), ...
           get_v2(data_15v{3}) ];

v1_avg_exp = mean(v1_exp, 2);
v2_avg_exp = mean(v2_exp, 2);

%% ========== SIMULATION ==========
% Simulation arrays
v1_sim = sim_data.v1sim;
v2_sim = sim_data.v2sim;

% Assuming simulation has same number of points, create time vector
t_sim = linspace(t_exp(1), t_exp(end), length(v1_sim))';

%% ========== PLOT ==========
figure; hold on;

v1_color = [0.6 0.6 0.6];       % experimental gray
v2_color = [1 0.6 0.6];         % experimental red
sim_color = [0 0.4470 0.7410];  % MATLAB default blue for simulation

% Plot experimental trials
plot(t_exp, v1_exp, 'Color', v1_color, 'LineWidth', 1.1);
plot(t_exp, v2_exp, '--', 'Color', v2_color, 'LineWidth', 1.1);

% Plot experimental averages
plot(t_exp, v1_avg_exp, 'k', 'LineWidth', 2);
plot(t_exp, v2_avg_exp, 'r', 'LineWidth', 2);

% Plot simulation
plot(t_sim, v1_sim, ':', 'Color', sim_color, 'LineWidth', 2);
plot(t_sim, v2_sim, ':', 'Color', sim_color, 'LineWidth', 2);

xlabel('Time (s)');
ylabel('Output');
title('1.5 V Step Response: Experimental vs Simulation');
legend( ...
    'v1 Exp Trials', 'v2 Exp Trials', ...
    'v1 Exp Avg', 'v2 Exp Avg', ...
    'v1 Sim', 'v2 Sim' );
