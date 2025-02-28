#ifndef TYPES_HPP
#define TYPES_HPP

#ifdef _WIN32
// Windows-specific code
#define OS_NAME "Windows"
#elif __APPLE__
// macOS-specific code
#define OS_NAME "macOS"
#else
// Code for other platforms (if needed)
#define OS_NAME "Unknown"
#endif

#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <ctime>
#include <chrono>
#include <optional>
#include "neat/config.hpp"
#include "indicators/indicator.hpp"

class Indicator; // Forward declaration

/**
 * @brief Enum for different time frames.
 */
enum class TimeFrame
{
    M1,
    M5,
    M15,
    M30,
    H1,
    H4,
    H12,
    D1
};

/**
 * @brief Struct representing a candle.
 */
struct Candle
{
    time_t date; // Close date of the candle
    double open;
    double high;
    double low;
    double close;
    double tick_volume;
    double volume;
    double spread;
};

/**
 * @brief Type definitions for different data structures.
 */
using CandlesData = std::unordered_map<TimeFrame, std::vector<Candle>>;
using IndicatorsData = std::unordered_map<TimeFrame, std::map<std::string, std::vector<double>>>;
using BaseCurrencyConversionRateData = std::map<time_t, double>;

/**
 * @brief Struct representing cached data with date information.
 */
struct CachedData
{
    CandlesData candles;                  // Cached candle data
    IndicatorsData indicators;            // Cached indicator data
    double base_currency_conversion_rate; // Cached base currency conversion rates
};

/**
 * @brief Enum for position side (LONG or SHORT).
 */
enum class PositionSide
{
    LONG,
    SHORT
};

/**
 * @brief Enum for position information.
 */
enum class PositionInfo
{
    TYPE,
    PNL,
    DURATION,
};

/**
 * @brief Struct representing a trading position.
 */
struct Position
{
    PositionSide side;  // Side of the position
    double size;        // Size of the position
    double entry_price; // Entry price of the position
    time_t entry_date;  // Entry date of the position
    double pnl;         // Profit and Loss of the position
};

/**
 * @brief Enum for order type (TAKE_PROFIT or STOP_LOSS).
 */
enum class OrderType
{
    TAKE_PROFIT,
    STOP_LOSS
};

/**
 * @brief Enum for order side (LONG or SHORT).
 */
enum class OrderSide
{
    LONG,
    SHORT
};

/**
 * @brief Struct representing an order.
 */
struct Order
{
    OrderSide side; // Side of the order
    OrderType type; // Type of the order
    double price;   // Price of the order
};

/**
 * @brief Struct representing a trade.
 */
struct Trade
{
    PositionSide side;      // Side of the trade
    time_t entry_date;      // Entry date of the trade
    time_t exit_date;       // Exit date of the trade
    double entry_price;     // Entry price of the trade
    double exit_price;      // Exit price of the trade
    double size;            // Size of the trade
    double pnl;             // Profit and Loss of the trade
    double pnl_percent;     // Profit and Loss as a percentage of the balance
    double pnl_net_percent; // Profit and Loss minus the fees of the balance
    double fees;            // Fees of the trade
    int duration;           // Duration of the trade
    bool closed;            // Whether the trade is closed
};

/**
 * @brief Struct representing symbol information.
 */
struct SymbolInfo
{
    std::string asset;           // Asset of the symbol
    std::string base;            // Base currency of the symbol
    int decimal_places;          // Number of decimal places for the price precision
    double point_value;          // Value of one point movement in the symbol's price
    int contract_size;           // Contract size of the symbol
    double min_lot_size;         // Minimum lot size allowed for the symbol
    double max_lot_size;         // Maximum lot size allowed for the symbol
    double lot_size_step;        // Step size for lot size increments/decrements
    double commission_per_lot;   // Commission per lot traded for the symbol
    std::string commission_base; // Base currency for commission calculation
};

/**
 * @brief Struct representing general trading configuration.
 */
struct GeneralConfig
{
    std::string name;             // Name of the trading configuration
    std::string version;          // Version of the trading configuration
    std::string symbol;           // Trading symbol
    double initial_balance;       // Initial account balance
    std::string account_currency; // Account currency
    int leverage;                 // Leverage
};

/**
 * @brief Enum for different types of take profit/stop loss configurations.
 */
enum class TypeTakeProfitStopLoss
{
    POINTS,
    PERCENT,
    EXTREMUM,
    ATR,
};

/**
 * @brief Enum for different types of trailing stop loss configurations.
 */
enum class TypeTrailingStopLoss
{
    POINTS,
    PERCENT,
};

/**
 * @brief Struct representing take profit and stop loss configuration.
 */
struct TakeProfitStopLossConfig
{
    TypeTakeProfitStopLoss type_stop_loss;            // Type of stop loss
    std::optional<int> stop_loss_in_points;           // Stop loss in points
    std::optional<double> stop_loss_in_percent;       // Stop loss as a percentage
    std::optional<int> stop_loss_extremum_period;     // Stop loss period for extremum
    std::optional<int> stop_loss_atr_period;          // Stop loss period for ATR
    std::optional<double> stop_loss_atr_multiplier;   // Stop loss multiplier for ATR
    TypeTakeProfitStopLoss type_take_profit;          // Type of take profit
    std::optional<int> take_profit_in_points;         // Take profit in points
    std::optional<double> take_profit_in_percent;     // Take profit as a percentage
    std::optional<int> take_profit_extremum_period;   // Take profit period for extremum
    std::optional<int> take_profit_atr_period;        // Take profit period for ATR
    std::optional<double> take_profit_atr_multiplier; // Take profit multiplier for ATR
};

/**
 * @brief Struct representing trailing stop loss configuration.
 */
struct TrailingStopLossConfig
{
    TypeTrailingStopLoss type;                           // Type of trailing stop loss configuration (POINTS or PERCENT)
    std::optional<int> activation_level_in_points;       // Activation level in points before trailing stop loss is activated
    std::optional<double> activation_level_in_percent;   // Activation level as a percentage before trailing stop loss is activated
    std::optional<int> trailing_stop_loss_in_points;     // Trailing stop loss in points
    std::optional<double> trailing_stop_loss_in_percent; // Trailing stop loss as a percentage
};

/**
 * @brief Struct representing trading schedule.
 */
struct TradingSchedule
{
    std::vector<bool> monday;    // Trading schedule for Monday
    std::vector<bool> tuesday;   // Trading schedule for Tuesday
    std::vector<bool> wednesday; // Trading schedule for Wednesday
    std::vector<bool> thursday;  // Trading schedule for Thursday
    std::vector<bool> friday;    // Trading schedule for Friday
    std::vector<bool> saturday;  // Trading schedule for Saturday
    std::vector<bool> sunday;    // Trading schedule for Sunday
};

/**
 * @brief Struct representing trading strategy configuration.
 */
struct StrategyConfig
{
    TimeFrame timeframe;                                             // Time frame with which the strategy is used
    double risk_per_trade;                                           // Risk per trade in % of capital
    std::optional<int> maximum_trades_per_day;                       // Maximum trades per day allowed
    std::optional<double> maximum_spread;                            // Maximum spread allowed
    std::optional<int> minimum_trade_duration;                       // Minimum trade duration
    std::optional<int> maximum_trade_duration;                       // Maximum trade duration
    std::optional<int> minimum_duration_before_next_trade;           // Minimum duration before the next trade
    std::optional<bool> can_close_trade;                             // Whether the strategy can close a trade
    std::optional<bool> can_open_long_trade;                         // Whether the strategy can open a long trade
    std::optional<bool> can_open_short_trade;                        // Whether the strategy can open a short trade
    TakeProfitStopLossConfig take_profit_stop_loss_config;           // Take profit and stop loss configuration
    std::optional<TradingSchedule> trading_schedule;                 // Trading schedule
    std::optional<TrailingStopLossConfig> trailing_stop_loss_config; // Trailing stop loss configuration
};

/**
 * @brief Struct representing inputs for a neural network.
 */
struct NeuralNetworkInputs
{
    std::map<TimeFrame, std::vector<Indicator *>> indicators; // Indicators
    std::vector<PositionInfo> position;                       // Position information (TYPE, PNL, DURATION)
};

/**
 * @brief Struct representing training configuration.
 */
struct TrainingConfig
{
    int generations;                                 // Number of generations for training
    std::optional<double> bad_trader_threshold;      // If the trader balance is below this threshold, the trader dies
    std::optional<double> inactive_trader_threshold; // If during this number of candles the trader does not make any trade, the trader dies
    time_t training_start_date;                      // Start date for training
    time_t training_end_date;                        // End date for training
    time_t test_start_date;                          // Start date for testing
    time_t test_end_date;                            // End date for testing
    std::optional<double> decision_threshold;        // Below this threshold, the trader does not make any decision
    NeuralNetworkInputs inputs;                      // Inputs for neural network
};

/**
 * @brief Struct representing evaluation configuration.
 */
struct EvaluationConfig
{
    std::optional<bool> maximize_nb_trades;          // Maximize the number of trades
    std::optional<int> minimum_nb_trades;            // Minimum number of trades
    std::optional<int> maximum_trade_duration;       // Maximum trade duration
    std::optional<double> expected_return_per_day;   // Expected return per day in % of capital
    std::optional<double> expected_return_per_month; // Expected return per month in % of capital
    std::optional<double> expected_return;           // Expected return per year in % of capital
    std::optional<double> maximum_drawdown;          // Maximum drawdown in % of capital
    std::optional<double> minimum_winrate;           // Minimum win rate in %
    std::optional<double> minimum_profit_factor;     // Minimum profit factor
};

/**
 * @brief Struct representing overall trading configuration.
 */
struct Config
{
    GeneralConfig general;       // General trading configuration
    StrategyConfig strategy;     // Trading strategy configuration
    TrainingConfig training;     // Training configuration
    EvaluationConfig evaluation; // Evaluation configuration
    neat::Config neat;           // NEAT configuration
};

#endif /* TYPES_HPP */
