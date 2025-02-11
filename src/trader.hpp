#ifndef TRADER_HPP
#define TRADER_HPP

#include <ctime>
#include <vector>
#include <unordered_map>
#include "libs/json.hpp"
#include "neat/genome.hpp"
#include "utils/logger.hpp"
#include "trading/stats.hpp"
#include "types.hpp"

class Trader
{
public:
    Config config;
    SymbolInfo symbol_info;

    // Vision
    CandlesData candles;
    double current_base_currency_conversion_rate;
    time_t current_date;

    // History
    std::vector<double> balance_history;
    std::vector<Trade> trades_history;

    // Trading stuffs
    double balance;
    Position *current_position;
    std::vector<Order> open_orders;
    int duration_in_position;   // Duration in the current position
    int duration_without_trade; // Countdown to avoid trading too much
    int nb_trades_today;        // Number of trades today

    // Neat stuffs
    neat::Genome *genome;
    int generation;
    double fitness;
    double score;
    std::vector<double> vision;
    std::vector<double> decisions;
    int lifespan;
    bool dead;

    // Statistics of the trader
    Stats stats;

    // Fitness evaluation details
    std::unordered_map<std::string, std::string> fitness_details;

    // Logger
    Logger *logger;

    /**
     * @brief Constructor for the Trader class.
     * @param genome Genome object.
     * @param config Configuration object.
     * @param logger Logger object.
     */
    Trader(neat::Genome *genome, Config config, Logger *logger = nullptr);

    /**
     * @brief Destructor for the Trader class.
     */
    ~Trader();

    /**
     * @brief Get inputs for genome.
     * @param indicators Indicator data for all time frames.
     * @param base_currency_conversion_rate Conversion rate when the base asset traded is different from the account currency.
     * @param position_infos Vector of position information.
     */
    void look(IndicatorsData &indicators, double base_currency_conversion_rate, std::vector<PositionInfo> position_infos);

    /**
     * @brief Get the outputs from the neural network.
     */
    void think();

    /**
     * @brief Update the trader.
     * - Detect a new day and reset the number of trades made today.
     * - Update the current date and candles.
     * - Increment the position duration.
     * - Update the position PNL.
     * - Update the trailing stop loss.
     * - Check open orders.
     * - Check position liquidation.
     * - Close the trade before a rest day.
     * - Update the lifespan.
     * - Check if the trader is bad or inactive.
     * - Update the balance history.
     *
     * @param candles Candle data for all time frames.
     */
    void update(CandlesData &candles);

    /**
     * @brief Check if the trader can trade.
     */
    bool can_trade();

    /**
     * @brief Trade according to the decision.
     * @return 1 if the trader opened a long position, 2 if the trader opened a short position, 3 if the trader closed a the position, 0 if the trader wait.
     */
    int trade();

    /**
     * @brief Calculate the fitness of the trader.
     */
    void calculate_fitness();

    /**
     * @brief Calculate the score of the trader.
     */
    void calculate_score();

    /**
     * @brief Calcule the trader statistics.
     */
    void calculate_stats();

    /**
     * @brief Open a position by market.
     * @param price Price of the market order.
     * @param size Size of the market order.
     * @param side Side of the market order.
     */
    void open_position_by_market(double price, double size, OrderSide side);

    /**
     * @brief Open a position by limit.
     * @param price Price of the limit order.
     * @param size Size of the limit order.
     * @param side Side of the limit order.
     */
    void close_position_by_market(double price = 0.0);

    /**
     * @brief Close a position by limit.
     * @param price Price of the limit order.
     */
    void close_position_by_limit(double price);

    /**
     * @brief Create an open order.
     * @param type Type of the order.
     * @param side Side of the order.
     * @param price Price of the order.
     */
    void create_open_order(OrderType type, OrderSide side, double price);

    /**
     * @brief Check the open orders and activate them if the price crosses.
     */
    void check_open_orders();

    /**
     * @brief Close all the open orders.
     */
    void close_open_orders();

    /**
     * @brief Check if the position got liquidated.
     */
    void check_position_liquidation();

    /**
     * @brief Update position profit and loss.
     * @param price Price of the asset.
     */
    void update_position_pnl(double price = 0.0);

    /**
     * @brief Update the trailing stop loss.
     */
    void update_trailing_stop_loss();

    /**
     * @brief Print the statistics of the trader in the console.
     */
    void print_stats_to_console();

    /**
     * @brief Print the fitness details of the trader in the console.
     */
    void print_fitness_details_to_console();

    /**
     * @brief Converts the trader to a JSON object.
     * @return JSON representation of the trader.
     */
    nlohmann::json to_json() const;

    /**
     * @brief Creates a trader from a JSON object.
     * @param json JSON object representing the trader.
     * @return Trader created from the JSON object.
     */
    static Trader *from_json(nlohmann::json &json, Config &config, Logger *logger = nullptr);

    /**
     * @brief Generate the graph of the balance history.
     * @param filename Filename of the graph.
     */
    void generate_balance_history_graph(const std::string &filename);

    /**
     * @brief Print the statistics aanddn the trades list of the trader in a HTML file.
     * @param filename Filename of the HTML file.
     * @param start_date Start date of the report.
     * @param end_date End date of the report.
     */
    void generate_report(const std::string &filename, time_t start_date, time_t end_date);

private:
    /**
     * @brief Display the common log header.
     * @return String representation of the log header.
     */
    std::string log_header();

    /**
     * @brief Display the current position.
     * @return String representation of the current position.
     */
    std::string current_position_to_string();

    /**
     * @brief Display the open orders.
     * @return String representation of the open orders.
     */
    std::string open_orders_to_string();
};

#endif // TRADER_HPP