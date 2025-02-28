#ifndef MOMENTUM_INDICATORS_HPP
#define MOMENTUM_INDICATORS_HPP

#include <variant>
#include <functional>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include "builder.hpp"
#include "../types.hpp"
#include "indicator.hpp"

/**
 * Awesome Oscillator
 *
 * From: https://www.tradingview.com/wiki/Awesome_Oscillator_(AO)
 *
 * The Awesome Oscillator is an indicator used to measure market momentum. AO calculates the difference of a 34 Period and 5 Period Simple Moving Averages. The Simple Moving Averages that are used are not calculated using closing price but rather each bar�s midpoints. AO is generally used to affirm trends or to anticipate possible reversals.
 *
 * From: https://www.ifcm.co.uk/ntx-indicators/awesome-oscillator
 *
 * Awesome Oscillator is a 34-period simple moving average, plotted through the central points of the bars (H+L)/2, and subtracted from the 5-period simple moving average, graphed across the central points of the bars (H+L)/2.
 *
 * MEDIAN PRICE = (HIGH+LOW)/2
 *
 * AO = SMA(MEDIAN PRICE, 5)-SMA(MEDIAN PRICE, 34)
 *
 * where
 *
 * SMA � Simple Moving Average.
 */
class AwesomeOscillator : public Indicator
{
public:
    /**
     * @brief Construct a new AwesomeOscillator object.
     *
     * @param offset Offset value. Default is 0.
     */
    AwesomeOscillator(int offset = 0);

    /**
     * @brief Calculate the AwesomeOscillator values.
     *
     * @param candles Vector of Candle data.
     * @param normalize_data Boolean flag indicating whether to normalize data.
     * @return std::vector<double> Vector containing calculated values.
     */
    std::vector<double> calculate(const std::vector<Candle> &candles, bool normalize_data = false) const override;
};

// *********************************************************************************************

/**
 * @brief Class to calculate Kaufman's Adaptive Moving Average (KAMA) indicator.
 */
class KAMA : public Indicator
{
public:
    /**
     * @brief Construct a new KAMA object.
     *
     * @param er_period Period for the Efficiency Ratio (ER). Default is 10.
     * @param fastest_sc_period Period for the fastest Smoothing Constant (SC). Default is 2.
     * @param slowest_sc_period Period for the slowest Smoothing Constant (SC). Default is 30.
     * @param offset Offset value. Default is 0.
     */
    KAMA(int er_period = 10, int fastest_sc_period = 2, int slowest_sc_period = 30, int offset = 0);

    /**
     * @brief Calculate Kaufman's Adaptive Moving Average (KAMA).
     *
     * @param candles Vector of Candle data.
     * @param normalize_data Boolean flag indicating whether to normalize data.
     * @return std::vector<double> Vector containing the calculated KAMA values.
     */
    std::vector<double> calculate(const std::vector<Candle> &candles, bool normalize_data = false) const override;

private:
    /**
     * @brief Calculate the Efficiency Ratio (ER).
     *
     * @param closes Vector of closing prices.
     * @return std::vector<double> Vector containing the calculated ER values.
     */
    std::vector<double> calculate_er(const std::vector<double> &closes) const;

    /**
     * @brief Calculate the Smoothing Constant (SC).
     *
     * @param er_values Vector of Efficiency Ratio (ER) values.
     * @return std::vector<double> Vector containing the calculated SC values.
     */
    std::vector<double> calculate_sc(const std::vector<double> &er_values) const;

    /**
     * @brief Calculate the initial KAMA (Simple Moving Average).
     *
     * @param closes Vector of closing prices.
     * @return double Initial KAMA value.
     */
    double calculate_initial_kama(const std::vector<double> &closes) const;
};

// *********************************************************************************************

/**
 * MFI (Money Flow Index)
 *
 * Is a momentum indicator that measures the inflow and outflow of money into an asset over a specific period of time.
 */
class MFI : public Indicator
{
public:
    /**
     * @brief Construct a new Money Flow Index object.
     *
     * @param period The period for calculating Money Flow Index (MFI). Default is 14.
     * @param offset Offset value. Default is 0.
     */
    MFI(int period = 14, int offset = 0);

    /**
     * @brief Calculate the Money Flow Index (MFI) values.
     *
     * @param candles Vector of Candle data.
     * @param normalize_data Boolean flag indicating whether to normalize data.
     * @return std::vector<double> Vector containing calculated MFI values.
     */
    std::vector<double> calculate(const std::vector<Candle> &candles, bool normalize_data = false) const override;
};

// *********************************************************************************************

/**
 * The Percentage Price Oscillator (PPO) is a momentum oscillator that measures the difference between two moving averages as a percentage of the larger moving average.
 *
 * https://school.stockcharts.com/doku.php?id=technical_indicators:price_oscillators_ppo
 */
class PPO : public Indicator
{
public:
    /**
     * @brief Construct a new PPO object with a specified short period, long period, and offset.
     *
     * @param short_period The short period for calculating PPO (default is 12).
     * @param long_period The long period for calculating PPO (default is 26).
     * @param offset The offset value (default is 0).
     */
    PPO(int short_period = 12, int long_period = 26, int offset = 0);

    /**
     * @brief Calculate the Price Oscillator (PPO) for a given set of candles.
     *
     * @param candles Vector of Candle data.
     * @param normalize_data Boolean flag indicating whether to normalize data.
     * @return std::vector<double> Vector containing calculated PPO values.
     */
    std::vector<double> calculate(const std::vector<Candle> &candles, bool normalize_data = false) const override;
};

// *********************************************************************************************

/**
 * The Percentage Volume Oscillator (PVO) is a momentum oscillator for volume. The PVO measures the difference between two volume-based moving averages as a percentage of the larger moving average.
 *
 * https://school.stockcharts.com/doku.php?id=technical_indicators:percentage_volume_oscillator_pvo
 */
class PVO : public Indicator
{
public:
    /**
     * @brief Construct a new Percentage Volume Oscillator (PVO) object.
     *
     * @param fast_period The fast period used for calculating the PVO. Default is 12.
     * @param slow_period The slow period used for calculating the PVO. Default is 26.
     * @param signal_period The signal period used for calculating the PVO signal line. Default is 9.
     * @param offset Offset value. Default is 0.
     */
    PVO(int fast_period = 12, int slow_period = 26, int signal_period = 9, int offset = 0);

    /**
     * @brief Calculate the Percentage Volume Oscillator (PVO) values.
     *
     * @param candles Vector of Candle data.
     * @param normalize_data Boolean flag indicating whether to normalize data.
     * @return std::vector<double> Vector containing calculated PVO values.
     */
    std::vector<double> calculate(const std::vector<Candle> &candles, bool normalize_data = false) const override;
};

// *********************************************************************************************

/**
 * Rate of Change (ROC)
 *
 * The Rate-of-Change (ROC) indicator, which is also referred to as simply Momentum, is a pure momentum oscillator that measures the percent change in price from one period to the next. The ROC calculation compares the current price with the price �n� periods ago. The plot forms an oscillator that fluctuates above and below the zero line as the Rate-of-Change moves from positive to negative. As a momentum oscillator, ROC signals include centerline crossovers, divergences and overbought-oversold readings. Divergences fail to foreshadow reversals more often than not, so this article will forgo a detailed discussion on them. Even though centerline crossovers are prone to whipsaw, especially short-term, these crossovers can be used to identify the overall trend. Identifying overbought or oversold extremes comes naturally to the Rate-of-Change oscillator.
 *
 * https://school.stockcharts.com/doku.php?id=technical_indicators:rate_of_change_roc_and_momentum
 */
class ROC : public Indicator
{
public:
    /**
     * @brief Construct a new ROC object.
     *
     * @param period Period value. Default is 9.
     * @param offset Offset value. Default is 0.
     */
    ROC(int period = 9, int offset = 0);

    /**
     * @brief Calculate the Rate of Change (ROC) values.
     *
     * @param candles Vector of Candle data.
     * @param normalize_data Boolean flag indicating whether to normalize data.
     * @return std::vector<double> Vector containing calculated values.
     */
    std::vector<double> calculate(const std::vector<Candle> &candles, bool normalize_data = false) const override;
};

// *********************************************************************************************

/**
 * Relative Strength Index (RSI)
 *
 * Compares the magnitude of recent gains and losses over a specified time period to measure speed and change of price movements of a security. It is primarily used to attempt to identify overbought or oversold conditions in the trading of an asset.
 *
 * https://www.investopedia.com/terms/r/rsi.asp
 */
class RSI : public Indicator
{
public:
    /**
     * @brief Construct a new RSI object.
     *
     * @param period Period value. Default is 14.
     * @param offset Offset value. Default is 0.
     */
    RSI(int period = 14, int offset = 0);

    /**
     * @brief Calculate the Relative Strength Index (RSI) values.
     *
     * @param candles Vector of Candle data.
     * @param normalize_data Boolean flag indicating whether to normalize data.
     * @return std::vector<double> Vector containing calculated values.
     */
    std::vector<double> calculate(const std::vector<Candle> &candles, bool normalize_data = false) const override;
};

// *********************************************************************************************

/**
 * Stochastic RSI
 *
 * The StochRSI oscillator was developed to take advantage of both momentum indicators in order to create a more sensitive indicator that is attuned to a specific security�s historical performance rather than a generalized analysis of price change.
 *
 * https://school.stockcharts.com/doku.php?id=technical_indicators:stochrsi https://www.investopedia.com/terms/s/stochrsi.asp
 */
class StochasticRSI : public Indicator
{
public:
    /**
     * @brief Construct a new StochasticRSI object.
     *
     * @param period Period value. Default is 14.
     * @param sma_period SMA Period value. Default is 3.
     * @param offset Offset value. Default is 0.
     */
    StochasticRSI(int period = 14, int sma_period = 3, int offset = 0);

    /**
     * @brief Calculate the Stochastic Relative Strength Index (Stoch RSI) values.
     *
     * @param candles Vector of Candle data.
     * @param normalize_data Boolean flag indicating whether to normalize data.
     * @return std::vector<double> Vector containing calculated values.
     */
    std::vector<double> calculate(const std::vector<Candle> &candles, bool normalize_data = false) const override;
};

// *********************************************************************************************

/**
 * Stochastic Oscillator
 *
 * Developed in the late 1950s by George Lane. The stochastic oscillator presents the location of the closing price of a stock in relation to the high and low range of the price of a stock over a period of time, typically a 14-day period.
 *
 * https://school.stockcharts.com/doku.php?id=technical_indicators:stochastic_oscillator_fast_slow_and_full
 */
class StochasticOscillator : public Indicator
{
public:
    /**
     * @brief Construct a new StochasticOscillator object.
     *
     * @param k_period K Period value. Default is 14.
     * @param d_period D Period value. Default is 3.
     * @param offset Offset value. Default is 0.
     */
    StochasticOscillator(int k_period = 14, int d_period = 3, int offset = 0);

    /**
     * @brief Calculate the Stochastic Oscillator values.
     *
     * @param candles Vector of Candle data.
     * @param normalize_data Boolean flag indicating whether to normalize data.
     * @return std::vector<double> Vector containing calculated values.
     */
    std::vector<double> calculate(const std::vector<Candle> &candles, bool normalize_data = false) const override;
};

// *********************************************************************************************

/**
 * True strength index (TSI)
 *
 * Shows both trend direction and overbought/oversold conditions.
 *
 * https://school.stockcharts.com/doku.php?id=technical_indicators:true_strength_index
 */
class TSI : public Indicator
{
public:
    /**
     * @brief Construct a new TSI object.
     *
     * @param short_period Short period value. Default is 13.
     * @param long_period Long period value. Default is 25.
     * @param offset Offset value. Default is 0.
     */
    TSI(int short_period = 13, int long_period = 25, int offset = 0);

    /**
     * @brief Calculate the TSI values.
     *
     * @param candles Vector of Candle data.
     * @param normalize_data Boolean flag indicating whether to normalize data.
     * @return std::vector<double> Vector containing calculated values.
     */
    std::vector<double> calculate(const std::vector<Candle> &candles, bool normalize_data = false) const override;
};

// *********************************************************************************************

/**
 * Ultimate Oscillator
 *
 * Developed by Larry Williams in 1976 and described in Stocks & Commodities Magazine in 1985. It is a momentum oscillator that reflects the overall tendency of three timeframes.
 *
 * https://school.stockcharts.com/doku.php?id=technical_indicators:ultimate_oscillator
 */
class UO : public Indicator
{
public:
    /**
     * @brief Construct a new Ultimate Oscillator object.
     *
     * @param period1 Period value for the first time frame. Default is 7.
     * @param period2 Period value for the second time frame. Default is 14.
     * @param period3 Period value for the third time frame. Default is 28.
     * @param offset Offset value. Default is 0.
     */
    UO(int period1 = 7, int period2 = 14, int period3 = 28, int offset = 0);

    /**
     * @brief Calculate the Ultimate Oscillator values.
     *
     * @param candles Vector of Candle data.
     * @param normalize_data Boolean flag indicating whether to normalize data.
     * @return std::vector<double> Vector containing calculated values.
     */
    std::vector<double> calculate(const std::vector<Candle> &candles, bool normalize_data = false) const override;
};

// *********************************************************************************************

/**
 * Williams %R
 *
 * Developed by Larry Williams, Williams %R is a momentum indicator that is the inverse of the Fast Stochastic Oscillator. Also referred to as %R, Williams %R reflects the level of the close relative to the highest high for the look-back period. In contrast, the Stochastic Oscillator reflects the level of the close relative to the lowest low. %R corrects for the inversion by multiplying the raw value by -100. As a result, the Fast Stochastic Oscillator and Williams %R produce the exact same lines, only the scaling is different. Williams %R oscillates from 0 to -100.
 *
 * Readings from 0 to -20 are considered overbought. Readings from -80 to -100 are considered oversold.
 *
 * Unsurprisingly, signals derived from the Stochastic Oscillator are also applicable to Williams %R.
 *
 * %R = (Highest High - Close)/(Highest High - Lowest Low) * -100
 *
 * Lowest Low = lowest low for the look-back period Highest High = highest high for the look-back period %R is multiplied by -100 correct the inversion and move the decimal.
 *
 * https://school.stockcharts.com/doku.php?id=technical_indicators:williams_r
 *
 * The Williams %R oscillates from 0 to -100. When the indicator produces readings from 0 to -20, this indicates overbought market conditions. When readings are -80 to -100, it indicates oversold market conditions.
 */
class WPR : public Indicator
{
public:
    /**
     * @brief Construct a new Williams Percent R object.
     *
     * @param period The period for calculating Williams %R. Default to 14.
     * @param offset Offset value. Default is 0.
     */
    WPR(int period = 14, int offset = 0);

    /**
     * @brief Calculate the Williams Percent R values.
     *
     * @param candles Vector of Candle data.
     * @param normalize_data Boolean flag indicating whether to normalize data.
     * @return std::vector<double> Vector containing calculated values.
     */
    std::vector<double> calculate(const std::vector<Candle> &candles, bool normalize_data = false) const override;
};

const std::unordered_map<std::string, std::function<Indicator *(std::unordered_map<std::string, IndicatorParam>)>> momentum_indicators_map = {
    {"awesome-oscillator", [](std::unordered_map<std::string, IndicatorParam> params) -> Indicator *
     {
         try
         {
             if (check_params(params, {{"offset", typeid(int)}}))
             {
                 int offset = std::get<int>(params["offset"]);
                 return new AwesomeOscillator(offset);
             }
         }
         catch (const std::exception &e)
         {
             std::cerr << "Error creating AwesomeOscillator: " << e.what() << std::endl;
             std::exit(1);
         }

         return nullptr;
     }},
    {"kama", [](std::unordered_map<std::string, IndicatorParam> params) -> Indicator *
     {
         try
         {
             if (check_params(params, {{"er_period", typeid(int)}, {"fastest_sc_period", typeid(int)}, {"slowest_sc_period", typeid(int)}, {"offset", typeid(int)}}))
             {
                 int er_period = std::get<int>(params["er_period"]);
                 int fastest_sc_period = std::get<int>(params["fastest_sc_period"]);
                 int slowest_sc_period = std::get<int>(params["slowest_sc_period"]);
                 int offset = std::get<int>(params["offset"]);
                 return new KAMA(er_period, fastest_sc_period, slowest_sc_period, offset);
             }
         }
         catch (const std::exception &e)
         {
             std::cerr << "Error creating KAMA: " << e.what() << std::endl;
             std::exit(1);
         }

         return nullptr;
     }},
    {"rsi", [](std::unordered_map<std::string, IndicatorParam> params) -> Indicator *
     {
         try
         {
             if (check_params(params, {{"period", typeid(int)}, {"offset", typeid(int)}}))
             {
                 int period = std::get<int>(params["period"]);
                 int offset = std::get<int>(params["offset"]);
                 return new RSI(period, offset);
             }
         }
         catch (const std::exception &e)
         {
             std::cerr << "Error creating RSI: " << e.what() << std::endl;
             std::exit(1);
         }

         return nullptr;
     }},
    {"mfi", [](std::unordered_map<std::string, IndicatorParam> params) -> Indicator *
     {
         try
         {
             if (check_params(params, {{"period", typeid(int)}, {"offset", typeid(int)}}))
             {
                 int period = std::get<int>(params["period"]);
                 int offset = std::get<int>(params["offset"]);
                 return new MFI(period, offset);
             }
         }
         catch (const std::exception &e)
         {
             std::cerr << "Error creating MFI: " << e.what() << std::endl;
             std::exit(1);
         }

         return nullptr;
     }},
    {"ppo", [](std::unordered_map<std::string, IndicatorParam> params) -> Indicator *
     {
         try
         {
             if (check_params(params, {{"short_period", typeid(int)}, {"long_period", typeid(int)}, {"offset", typeid(int)}}))
             {
                 int short_period = std::get<int>(params["short_period"]);
                 int long_period = std::get<int>(params["long_period"]);
                 int offset = std::get<int>(params["offset"]);
                 return new PPO(short_period, long_period, offset);
             }
         }
         catch (const std::exception &e)
         {
             std::cerr << "Error creating PPO: " << e.what() << std::endl;
             std::exit(1);
         }

         return nullptr;
     }},
    {"pvo", [](std::unordered_map<std::string, IndicatorParam> params) -> Indicator *
     {
         try
         {
             if (check_params(params, {{"fast_period", typeid(int)}, {"slow_period", typeid(int)}, {"signal_period", typeid(int)}, {"offset", typeid(int)}}))
             {
                 int fast_period = std::get<int>(params["fast_period"]);
                 int slow_period = std::get<int>(params["slow_period"]);
                 int signal_period = std::get<int>(params["signal_period"]);
                 int offset = std::get<int>(params["offset"]);
                 return new PVO(fast_period, slow_period, signal_period, offset);
             }
         }
         catch (const std::exception &e)
         {
             std::cerr << "Error creating PVO: " << e.what() << std::endl;
             std::exit(1);
         }

         return nullptr;
     }},
    {"roc", [](std::unordered_map<std::string, IndicatorParam> params) -> Indicator *
     {
         try
         {
             if (check_params(params, {{"period", typeid(int)}, {"offset", typeid(int)}}))
             {
                 int period = std::get<int>(params["period"]);
                 int offset = std::get<int>(params["offset"]);
                 return new ROC(period, offset);
             }
         }
         catch (const std::exception &e)
         {
             std::cerr << "Error creating ROC: " << e.what() << std::endl;
             std::exit(1);
         }

         return nullptr;
     }},
    {"rsi", [](std::unordered_map<std::string, IndicatorParam> params) -> Indicator *
     {
         try
         {
             if (check_params(params, {{"period", typeid(int)}, {"offset", typeid(int)}}))
             {
                 int period = std::get<int>(params["period"]);
                 int offset = std::get<int>(params["offset"]);
                 return new RSI(period, offset);
             }
         }
         catch (const std::exception &e)
         {
             std::cerr << "Error creating RSI: " << e.what() << std::endl;
             std::exit(1);
         }

         return nullptr;
     }},
    {"stochastic-rsi", [](std::unordered_map<std::string, IndicatorParam> params) -> Indicator *
     {
         try
         {
             if (check_params(params, {{"period", typeid(int)}, {"sma_period", typeid(int)}, {"offset", typeid(int)}}))
             {
                 int period = std::get<int>(params["period"]);
                 int sma_period = std::get<int>(params["sma_period"]);
                 int offset = std::get<int>(params["offset"]);
                 return new StochasticRSI(period, sma_period, offset);
             }
         }
         catch (const std::exception &e)
         {
             std::cerr << "Error creating StochasticRSI: " << e.what() << std::endl;
             std::exit(1);
         }

         return nullptr;
     }},
    {"stochastic-oscillator", [](std::unordered_map<std::string, IndicatorParam> params) -> Indicator *
     {
         try
         {
             if (check_params(params, {{"k_period", typeid(int)}, {"d_period", typeid(int)}, {"offset", typeid(int)}}))
             {
                 int k_period = std::get<int>(params["k_period"]);
                 int d_period = std::get<int>(params["d_period"]);
                 int offset = std::get<int>(params["offset"]);
                 return new StochasticOscillator(k_period, d_period, offset);
             }
         }
         catch (const std::exception &e)
         {
             std::cerr << "Error creating StochasticOscillator: " << e.what() << std::endl;
             std::exit(1);
         }

         return nullptr;
     }},
    {"tsi", [](std::unordered_map<std::string, IndicatorParam> params) -> Indicator *
     {
         try
         {
             if (check_params(params, {{"short_period", typeid(int)}, {"long_period", typeid(int)}, {"offset", typeid(int)}}))
             {
                 int short_period = std::get<int>(params["short_period"]);
                 int long_period = std::get<int>(params["long_period"]);
                 int offset = std::get<int>(params["offset"]);
                 return new TSI(short_period, long_period, offset);
             }
         }
         catch (const std::exception &e)
         {
             std::cerr << "Error creating TSI: " << e.what() << std::endl;
             std::exit(1);
         }

         return nullptr;
     }},
    {"uo", [](std::unordered_map<std::string, IndicatorParam> params) -> Indicator *
     {
         try
         {
             if (check_params(params, {{"period1", typeid(int)}, {"period2", typeid(int)}, {"period3", typeid(int)}, {"offset", typeid(int)}}))
             {
                 int period1 = std::get<int>(params["period1"]);
                 int period2 = std::get<int>(params["period2"]);
                 int period3 = std::get<int>(params["period3"]);
                 int offset = std::get<int>(params["offset"]);
                 return new UO(period1, period2, period3, offset);
             }
         }
         catch (const std::exception &e)
         {
             std::cerr << "Error creating UO: " << e.what() << std::endl;
             std::exit(1);
         }

         return nullptr;
     }},
    {"wpr", [](std::unordered_map<std::string, IndicatorParam> params) -> Indicator *
     {
         try
         {
             if (check_params(params, {{"period", typeid(int)}, {"offset", typeid(int)}}))
             {
                 int period = std::get<int>(params["period"]);
                 int offset = std::get<int>(params["offset"]);
                 return new WPR(period, offset);
             }
         }
         catch (const std::exception &e)
         {
             std::cerr << "Error creating WPR: " << e.what() << std::endl;
             std::exit(1);
         }

         return nullptr;
     }},
};

#endif /* MOMENTUM_INDICATORS_HPP */