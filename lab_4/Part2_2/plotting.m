%====================================================================
% Plot comparison of experiment and simulation for Part 2.2
%====================================================================

clear; clc; close all;

%--------------------------
% Load data
%--------------------------
exp = load('experiment/2_2_data.mat');          % expected fields: t, x1, x2, xr, u
sim = load('simulation/2_2_simulation.mat');    % expected fields: t, x1, x2, xr, u

%--------------------------
% Figure setup
%--------------------------
figure('Name', 'Experiment vs Simulation - Part 2.2', 'Color', 'w');
tiledlayout(4,1,'Padding','compact','TileSpacing','compact');

%--------------------------
% (1) Cart 1 position: x1 vs t
%--------------------------
nexttile;
plot(exp.ScopeData1.time, exp.x1exp.signals.values, 'b-', 'LineWidth', 1.2); hold on;
plot(sim.tout, sim.x1sim.signals.values, 'r--', 'LineWidth', 1.2);
ylabel('x1(t)');
title('Cart 1 Position');
legend('Experiment','Simulation','Location','best');

%--------------------------
% (2) Commanded trajectory and cart 2 position: xr and x2 vs t
%--------------------------
nexttile;
plot(exp.ScopeData1.time, exp.xr.signals.values, 'k-', 'LineWidth', 1.2); hold on;
plot(exp.ScopeData1.time, exp.x2exp.signals.values, 'b-', 'LineWidth', 1.2);
plot(sim.tout, sim.x2sim.signals.values, 'r--', 'LineWidth', 1.2);
ylabel('Position');
title('Commanded Trajectory and Cart 2 Position');
legend('x_r (command)', 'x_2 exp', 'x_2 sim', 'Location','best');

%--------------------------
% (3) Cart 2 tracking error e = xr - x2
%--------------------------
nexttile;
e_exp = exp.xr.signals.values - exp.x2exp.signals.values;
e_sim = sim.xr.signals.values - sim.x2sim.signals.values;
plot(exp.ScopeData1.time, e_exp, 'b-', 'LineWidth', 1.2); hold on;
plot(sim.tout, e_sim, 'r--', 'LineWidth', 1.2);
ylabel('e(t)');
title('Cart 2 Tracking Error');
legend('Experiment','Simulation','Location','best');

%--------------------------
% (4) Control signal u
%--------------------------
nexttile;
plot(exp.ScopeData1.time, exp.uexp.signals.values, 'b-', 'LineWidth', 1.2); hold on;
plot(sim.tout, sim.usim.signals.values, 'r--', 'LineWidth', 1.2);
ylabel('u(t)');
xlabel('Time [s]');
title('Control Signal');
legend('Experiment','Simulation','Location','best');

%--------------------------
% Improve layout
%--------------------------
set(gcf, 'Position', [200 80 800 900]);
