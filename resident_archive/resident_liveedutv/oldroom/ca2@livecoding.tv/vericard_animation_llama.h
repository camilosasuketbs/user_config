

#pragma once


namespace vericard
{


   class animation_llama :
      virtual public animation
   {
   public:


      class llama
      {
      public:

         double   m_dSize;
         double   m_dSpeed;
         double   m_dColor;
         double   m_dColorSpeed;
         int      m_iOffset;
         rect     m_rect;
         int      m_iLastTop;
         double                           m_dVel;
         ::draw2d::dib_sp                 m_dib;

      };

      class light
      {
      public:
         point    m_pt;
         int      m_iBall;
         double   m_dPhase;
         double   m_dAngle;
         double   m_dColor;
         double   m_dColorSpeed;


      };


      rect                             m_rectDisc;
      int                              m_iLastTop2;
      ::visual::dib_sp                 m_dibDiscoBall;
      ::visual::dib_sp                 m_dibLlama;
      int                              m_iLlamaFloor;
      int                              m_iLlama;
      array < llama >                  m_llama;
      DWORD                            m_dwLastAddLlama;
      DWORD                            m_dwLlama;

      ::draw2d::dib_sp                 m_dibLights;
      array < light >                  m_lighta;
      size                             m_sizeLight;
      double                           m_dLightAperture;
      double                           m_dBallDistance;
      double                           m_dPhase;
      double                           m_dDiscoColor;
      ::visual::dib_sp                 m_dibDisco;



      animation_llama(pack * ppack);
      ~animation_llama();



      virtual void defer_add_llama();

      virtual bool initialize() override;
      virtual bool reset() override;

      virtual void _001OnDrawBefore(::draw2d::graphics * pgraphics) override;

      virtual void _001OnDrawAfter(::draw2d::graphics * pgraphics) override;


   };


} // namespace vericard



