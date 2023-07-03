#ifndef TPOT_TPOTMONDRAW_H
#define TPOT_TPOTMONDRAW_H

#include "MicromegasGeometry.h"

#include <micromegas/MicromegasDefs.h>
#include <micromegas/MicromegasMapping.h>
#include <onlmon/OnlMonDraw.h>

#include <array>
#include <memory>
#include <string>  

class OnlMonDB;
class TCanvas;
class TH1;
class TPad;

class TpotMonDraw : public OnlMonDraw
{
  public:
  
  /// constructor
  TpotMonDraw(const std::string &name);
  
  /// destructor
  ~TpotMonDraw() override = default;

  int Init() override;
  int Draw(const std::string &what = "ALL") override;
  int MakeHtml(const std::string &what = "ALL") override;
  int SavePlot(const std::string &what = "ALL", const std::string &type = "png") override;

  // get detector names
  std::vector<std::string> get_detnames_sphenix() const
  { return m_detnames_sphenix; }

  // define signal sample window
  using sample_window_t = std::pair<int, int>;
  void set_sample_window_signal( const sample_window_t& value ) 
  { m_sample_window_signal = value; }
  
  private:

  TCanvas* get_canvas(const std::string& name, bool clear = true );
  TCanvas* create_canvas(const std::string &name);
  
  int draw_counters();
  int draw_detector_occupancy();
  int draw_resist_occupancy();
  
  using histogram_array_t = std::array<TH1*, MicromegasDefs::m_nfee>;
  
  // drawing options
  enum DrawOptions
  {
    None = 0,
    Logx = 1<<0,
    Logy = 1<<1,
    Logz = 1<<2,
    Colz = 1<<3
  };
  
  /// get detector dependent histogram array from base name
  histogram_array_t get_histograms( const std::string& name );  

  /// draw histogram array
  int draw_array( const std::string& name, const histogram_array_t&, unsigned int /*option*/ = DrawOptions::None );
  
  /// draw detector names in current canvas
  /** only works if canvas contains one of the properly formated TH2Poly histograms */
  void draw_detnames_sphenix( const std::string& suffix = std::string());
    
  /// mapping
  MicromegasMapping m_mapping;
  
  /// geometry
  MicromegasGeometry m_geometry;
  
  /// detector names 
  std::vector<std::string> m_detnames_sphenix;
  
  /// needed to get time axis right
  int TimeOffsetTicks = -1;
  
  // draw run and time in a given pad
  void draw_time( TPad*);
  
  // sample window
  sample_window_t m_sample_window_signal = {20, 40};
  
  // canvases
  std::vector<TCanvas*> m_canvas;
  std::unique_ptr<OnlMonDB> dbvars;
};

#endif /* TPOT_TPOTMONDRAW_H */
