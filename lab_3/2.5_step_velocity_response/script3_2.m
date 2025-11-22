%% --- File lists ---
files_1v  = {"2_5_1_01.mat",  "2_5_1_02.mat",  "2_5_1_03.mat"};
files_15v = {"2_5_15_01.mat", "2_5_15_02.mat", "2_5_15_03.mat"};

%% --- Helper to load data ---
load_trials = @(flist) cellfun(@(f) load(f), flist, 'UniformOutput', false);

data_1v  = load_trials(files_1v);
data_15v = load_trials(files_15v);

%% --- Extractors ---
get_time  = @(d) d.ScopeData_v1_fit.time(:);   % both v1 and v2 share time base
get_v1    = @(d) d.ScopeData_v1_fit.signals.values(:);
get_v2    = @(d) d.ScopeData_v2_fit.signals.values(:);
get_input = @(d) d.ScopeData_u.signals.values(:);   % if needed later

%% ========== 1.0 V TRIALS ==========
t1 = get_time(data_1v{1});  % assume common time base

v1_1v = [ get_v1(data_1v{1}), ...
          get_v1(data_1v{2}), ...
          get_v1(data_1v{3}) ];

v2_1v = [ get_v2(data_1v{1}), ...
          get_v2(data_1v{2}), ...
          get_v2(data_1v{3}) ];

v1_avg_1v = mean(v1_1v, 2);
v2_avg_1v = mean(v2_1v, 2);

figure; hold on;

% Define toned-down colors for v1 and v2 trials
v1_color = [0.6 0.6 0.6];  % muted gray
v2_color = [1 0.6 0.6];    % muted red

% v1 trials (3)
plot(t1, v1_1v(:,1), 'Color', v1_color, 'LineWidth', 1.1);
plot(t1, v1_1v(:,2), 'Color', v1_color, 'LineWidth', 1.1);
plot(t1, v1_1v(:,3), 'Color', v1_color, 'LineWidth', 1.1);

% v2 trials (3)
plot(t1, v2_1v(:,1), '--', 'Color', v2_color, 'LineWidth', 1.1);
plot(t1, v2_1v(:,2), '--', 'Color', v2_color, 'LineWidth', 1.1);
plot(t1, v2_1v(:,3), '--', 'Color', v2_color, 'LineWidth', 1.1);

% averages (2)
plot(t1, v1_avg_1v, 'k', 'LineWidth', 2);
plot(t1, v2_avg_1v, 'r', 'LineWidth', 2);

xlabel('Time (s)');
ylabel('Output');
title('1.0 V Step Response (v1 and v2)');
legend( ...
    'v1 Trial 1','v1 Trial 2','v1 Trial 3', ...
    'v2 Trial 1','v2 Trial 2','v2 Trial 3', ...
    'v1 Average', 'v2 Average' );

%% ========== 1.5 V TRIALS ==========
t2 = get_time(data_15v{1});

v1_15v = [ get_v1(data_15v{1}), ...
           get_v1(data_15v{2}), ...
           get_v1(data_15v{3}) ];

v2_15v = [ get_v2(data_15v{1}), ...
           get_v2(data_15v{2}), ...
           get_v2(data_15v{3}) ];

v1_avg_15v = mean(v1_15v, 2);
v2_avg_15v = mean(v2_15v, 2);

figure; hold on;

% v1 trials (3)
plot(t2, v1_15v(:,1), 'Color', v1_color, 'LineWidth', 1.1);
plot(t2, v1_15v(:,2), 'Color', v1_color, 'LineWidth', 1.1);
plot(t2, v1_15v(:,3), 'Color', v1_color, 'LineWidth', 1.1);

% v2 trials (3)
plot(t2, v2_15v(:,1), '--', 'Color', v2_color, 'LineWidth', 1.1);
plot(t2, v2_15v(:,2), '--', 'Color', v2_color, 'LineWidth', 1.1);
plot(t2, v2_15v(:,3), '--', 'Color', v2_color, 'LineWidth', 1.1);

% averages (2)
plot(t2, v1_avg_15v, 'k', 'LineWidth', 2);
plot(t2, v2_avg_15v, 'r', 'LineWidth', 2);

xlabel('Time (s)');
ylabel('Output');
title('1.5 V Step Response (v1 and v2)');
legend( ...
    'v1 Trial 1','v1 Trial 2','v1 Trial 3', ...
    'v2 Trial 1','v2 Trial 2','v2 Trial 3', ...
    'v1 Average', 'v2 Average' );
