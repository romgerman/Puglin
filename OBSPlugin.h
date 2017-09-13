#pragma once

#include <obs-module.h>
#include "puglin_list.h"

namespace Puglin {

	enum OptionalPluginCallback : unsigned long
	{
		OPCWidth       = 1 << 0,
		OPCHeight      = 1 << 1,
		OPCDefaults    = 1 << 2,
		OPCProperties  = 1 << 3,
		OPCUpdate      = 1 << 4,
		OPCActivate    = 1 << 5,
		OPCDeactivate  = 1 << 6,
		OPCShow        = 1 << 7,
		OPCHide        = 1 << 8,
		OPCVideoTick   = 1 << 9,
		OPCVideoRender = 1 << 10,
		OPCFilterVideo = 1 << 11,
		OPCFilterAudio = 1 << 12,
		OPCSave        = 1 << 13,
		OPCLoad        = 1 << 14,
		OPCMouseClick  = 1 << 15,
		OPCMouseMove   = 1 << 16,
		OPCMouseWheel  = 1 << 17,
		OPCFocus       = 1 << 18,
		OPCKeyClick    = 1 << 19,
		OPCFilterRemove    = 1 << 20,
		OPCTransitionStart = 1 << 21,
		OPCTransitionStop   = 1 << 22
	};
	
	class OBSPlugin
	{
	public:
		OBSPlugin(char* id, char* name, obs_source_type type, unsigned int flags) :	m_id(id), m_name(name), m_type(type), m_flags(flags) {}

		virtual void* OnCreate(obs_data_t* settings, obs_source_t* source) { return nullptr; }
		virtual void OnDestroy() {}
		
		virtual unsigned int GetWidth() { return 0; }
		virtual unsigned int GetHeight() { return 0; }

		//virtual void GetDefaults(obs_data_t *settings) {}

		virtual obs_properties_t* GetProperties() { return nullptr; }

		virtual void OnUpdate(obs_data_t* settings) {}

		virtual void OnActivate() {}
		virtual void OnDeactivate() {}

		virtual void OnShowed() {}
		virtual void OnHidden() {}
		
		virtual void OnVideoTick(float seconds) {}

		virtual void OnVideoRender(gs_effect_t* effect) {}

		virtual obs_source_frame* OnFilterVideo(struct obs_source_frame* frame) { return frame; }
		virtual obs_audio_data* OnFilterAudio(struct obs_audio_data* audio) { return audio; }

		// enum_active_sources?

		virtual void OnSave(obs_data_t* settings) {}
		virtual void OnLoad(obs_data_t* settings) {}

		virtual void OnMouseClick(const struct obs_mouse_event* event, int32_t type, bool mouse_up, uint32_t click_count) {}
		virtual void OnMouseMove(const struct obs_mouse_event* event, bool mouse_leave) {}
		virtual void OnMouseWheel(const struct obs_mouse_event* event, int x_delta,	int y_delta) {}

		virtual void OnFocus(bool focus) {}

		virtual void OnKeyClick(const struct obs_key_event* event, bool key_up) {}

		virtual void OnFilterRemove(obs_source_t* source) {}

		// audio_render?
		// enum_all_sources?

		virtual void OnTransitionStart() {}
		virtual void OnTransitionStop() {}

	protected:
		void RegisterPlugin(unsigned int flags)
		{
			m_source_info = {
				m_id,
				m_type,
				m_flags,
				OBSPlugin::GetNameI,
				OBSPlugin::OnCreateI,
				OBSPlugin::OnDestroyI,
				(flags & OPCWidth) ? OBSPlugin::GetWidthI : nullptr,
				(flags & OPCHeight) ? OBSPlugin::GetHeightI : nullptr,
				nullptr,//(flags & OPCDefaults) ? OBSPlugin::GetDefaultsI : nullptr,
				(flags & OPCProperties) ? OBSPlugin::GetPropertiesI : nullptr,
				(flags & OPCUpdate) ? OBSPlugin::OnUpdateI : nullptr,
				(flags & OPCActivate) ? OBSPlugin::OnActivateI : nullptr,
				(flags & OPCDeactivate) ? OBSPlugin::OnDeactivateI : nullptr,
				(flags & OPCShow) ? OBSPlugin::OnShowedI : nullptr,
				(flags & OPCHide) ? OBSPlugin::OnHiddenI : nullptr,
				(flags & OPCVideoTick) ? OBSPlugin::OnVideoTickI : nullptr,
				(flags & OPCVideoRender) ? OBSPlugin::OnVideoRenderI : nullptr,
				(flags & OPCFilterVideo) ? OBSPlugin::OnFilterVideoI : nullptr,
				(flags & OPCFilterAudio) ? OBSPlugin::OnFilterAudioI : nullptr,
				nullptr, // enum_active_sources
				(flags & OPCSave) ? OBSPlugin::OnSaveI : nullptr,
				(flags & OPCLoad) ? OBSPlugin::OnLoadI : nullptr,
				(flags & OPCMouseClick) ? OBSPlugin::OnMouseClickI : nullptr,
				(flags & OPCMouseMove) ? OBSPlugin::OnMouseMoveI : nullptr,
				(flags & OPCMouseWheel) ? OBSPlugin::OnMouseWheelI : nullptr,
				(flags & OPCFocus) ? OBSPlugin::OnFocusI : nullptr,
				(flags & OPCKeyClick) ? OBSPlugin::OnKeyClickI : nullptr,
				(flags & OPCFilterRemove) ? OBSPlugin::OnFilterRemoveI : nullptr,
				this, // type_data
				nullptr, // free_type_data
				nullptr, // audio_render
				nullptr, // enum_all_sources
				(flags & OPCTransitionStart) ? OBSPlugin::OnTransitionStartI : nullptr,
				(flags & OPCTransitionStop) ? OBSPlugin::OnTransitionStopI : nullptr
			};

			puglin_add_info(&m_source_info);
		}

	private:
		static const char* GetNameI(void* type_data)
		{
			return static_cast<OBSPlugin*>(type_data)->m_name;
		}

		static void* OnCreateI(obs_data_t* settings, obs_source_t* source) // Can we not use "obs-internal" to get private data?
		{
			return static_cast<OBSPlugin*>(obs_source_get_type_data(source))->OnCreate(settings, source);
		}
		static void OnDestroyI(void* data)
		{
			static_cast<OBSPlugin*>(data)->OnDestroy();
		}

		static unsigned int GetWidthI(void* data)
		{
			return static_cast<OBSPlugin*>(data)->GetWidth();
		}
		static unsigned int GetHeightI(void* data)
		{ 
			return static_cast<OBSPlugin*>(data)->GetHeight();
		}

		/*static void GetDefaultsI(obs_data_t *settings)
		{
			//static_cast<OBSPlugin*>(settings->)
			
		}*/

		static obs_properties_t* GetPropertiesI(void* data)
		{
			return static_cast<OBSPlugin*>(data)->GetProperties();
		}

		static void OnUpdateI(void* data, obs_data_t* settings)
		{
			static_cast<OBSPlugin*>(data)->OnUpdate(settings);
		}

		static void OnActivateI(void* data)
		{
			static_cast<OBSPlugin*>(data)->OnActivate();
		}
		static void OnDeactivateI(void* data)
		{
			static_cast<OBSPlugin*>(data)->OnDeactivate();
		}

		static void OnShowedI(void* data)
		{
			static_cast<OBSPlugin*>(data)->OnShowed();
		}
		static void OnHiddenI(void* data)
		{
			static_cast<OBSPlugin*>(data)->OnHidden();
		}

		static void OnVideoTickI(void* data, float seconds)
		{
			static_cast<OBSPlugin*>(data)->OnVideoTick(seconds);
		}

		static void OnVideoRenderI(void* data, gs_effect_t* effect)
		{
			static_cast<OBSPlugin*>(data)->OnVideoRender(effect);
		}
	
		static obs_source_frame* OnFilterVideoI(void* data, struct obs_source_frame* frame)
		{
			return static_cast<OBSPlugin*>(data)->OnFilterVideo(frame);
		}
		static obs_audio_data* OnFilterAudioI(void* data, struct obs_audio_data* audio)
		{ 
			return static_cast<OBSPlugin*>(data)->OnFilterAudio(audio);
		}

		static void OnSaveI(void* data, obs_data_t* settings)
		{
			static_cast<OBSPlugin*>(data)->OnSave(settings);
		}
		static void OnLoadI(void* data, obs_data_t* settings)
		{
			static_cast<OBSPlugin*>(data)->OnLoad(settings);
		}

		static void OnMouseClickI(void* data, const struct obs_mouse_event* event, int32_t type, bool mouse_up, uint32_t click_count)
		{
			static_cast<OBSPlugin*>(data)->OnMouseClick(event, type, mouse_up, click_count);
		}
		static void OnMouseMoveI(void* data, const struct obs_mouse_event* event, bool mouse_leave)
		{
			static_cast<OBSPlugin*>(data)->OnMouseMove(event, mouse_leave);
		}
		static void OnMouseWheelI(void* data, const struct obs_mouse_event* event, int x_delta, int y_delta)
		{
			static_cast<OBSPlugin*>(data)->OnMouseWheel(event, x_delta, y_delta);
		}

		static void OnFocusI(void* data, bool focus)
		{
			static_cast<OBSPlugin*>(data)->OnFocus(focus);
		}

		static void OnKeyClickI(void* data, const struct obs_key_event* event, bool key_up)
		{
			static_cast<OBSPlugin*>(data)->OnKeyClick(event, key_up);
		}

		static void OnFilterRemoveI(void* data, obs_source_t* source)
		{
			static_cast<OBSPlugin*>(data)->OnFilterRemove(source);
		}

		static void OnTransitionStartI(void* data)
		{
			static_cast<OBSPlugin*>(data)->OnTransitionStart();
		}
		static void OnTransitionStopI(void* data)
		{
			static_cast<OBSPlugin*>(data)->OnTransitionStop();
		}

	private:
		obs_source_info m_source_info;

	protected:
		char* m_id;
		char* m_name;
		obs_source_type m_type;
		unsigned int m_flags;
	};

}
