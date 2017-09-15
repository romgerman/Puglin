#include "OBSPlugin.h"

#include "puglin_list.h"

using namespace Puglin;

void OBSPlugin::RegisterPlugin(unsigned int flags)
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
		nullptr,//(flags & OPCDefaults) ? OBSPlugin::GetDefaultsI : nullptr, // lambda? (NOPE, lambda works only if not captures anything)
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
		(flags & OPCAudioRender) ? OBSPlugin::OnAudioRenderI : nullptr,
		nullptr, // enum_all_sources
		(flags & OPCTransitionStart) ? OBSPlugin::OnTransitionStartI : nullptr,
		(flags & OPCTransitionStop) ? OBSPlugin::OnTransitionStopI : nullptr
	};

	puglin_add_info(&m_source_info);
}

// ------ Internal callback functions

const char* OBSPlugin::GetNameI(void* type_data)
{
	return static_cast<OBSPlugin*>(type_data)->m_name;
}

void* OBSPlugin::OnCreateI(obs_data_t* settings, obs_source_t* source)
{
	return static_cast<OBSPlugin*>(obs_source_get_type_data(source))->OnCreate(settings, source);
}
void OBSPlugin::OnDestroyI(void* data)
{
	static_cast<OBSPlugin*>(data)->OnDestroy();
}

unsigned int OBSPlugin::GetWidthI(void* data)
{
	return static_cast<OBSPlugin*>(data)->GetWidth();
}
unsigned int OBSPlugin::GetHeightI(void* data)
{
	return static_cast<OBSPlugin*>(data)->GetHeight();
}

obs_properties_t* OBSPlugin::GetPropertiesI(void* data)
{
	return static_cast<OBSPlugin*>(data)->GetProperties();
}

void OBSPlugin::OnUpdateI(void* data, obs_data_t* settings)
{
	static_cast<OBSPlugin*>(data)->OnUpdate(settings);
}

void OBSPlugin::OnActivateI(void* data)
{
	static_cast<OBSPlugin*>(data)->OnActivate();
}
void OBSPlugin::OnDeactivateI(void* data)
{
	static_cast<OBSPlugin*>(data)->OnDeactivate();
}

void OBSPlugin::OnShowedI(void* data)
{
	static_cast<OBSPlugin*>(data)->OnShowed();
}
void OBSPlugin::OnHiddenI(void* data)
{
	static_cast<OBSPlugin*>(data)->OnHidden();
}

void OBSPlugin::OnVideoTickI(void* data, float seconds)
{
	static_cast<OBSPlugin*>(data)->OnVideoTick(seconds);
}

void OBSPlugin::OnVideoRenderI(void* data, gs_effect_t* effect)
{
	static_cast<OBSPlugin*>(data)->OnVideoRender(effect);
}

obs_source_frame* OBSPlugin::OnFilterVideoI(void* data, struct obs_source_frame* frame)
{
	return static_cast<OBSPlugin*>(data)->OnFilterVideo(frame);
}
obs_audio_data* OBSPlugin::OnFilterAudioI(void* data, struct obs_audio_data* audio)
{
	return static_cast<OBSPlugin*>(data)->OnFilterAudio(audio);
}

void OBSPlugin::OnSaveI(void* data, obs_data_t* settings)
{
	static_cast<OBSPlugin*>(data)->OnSave(settings);
}
void OBSPlugin::OnLoadI(void* data, obs_data_t* settings)
{
	static_cast<OBSPlugin*>(data)->OnLoad(settings);
}

void OBSPlugin::OnMouseClickI(void* data, const struct obs_mouse_event* event, int32_t type, bool mouse_up, uint32_t click_count)
{
	static_cast<OBSPlugin*>(data)->OnMouseClick(event, type, mouse_up, click_count);
}
void OBSPlugin::OnMouseMoveI(void* data, const struct obs_mouse_event* event, bool mouse_leave)
{
	static_cast<OBSPlugin*>(data)->OnMouseMove(event, mouse_leave);
}
void OBSPlugin::OnMouseWheelI(void* data, const struct obs_mouse_event* event, int x_delta, int y_delta)
{
	static_cast<OBSPlugin*>(data)->OnMouseWheel(event, x_delta, y_delta);
}

void OBSPlugin::OnFocusI(void* data, bool focus)
{
	static_cast<OBSPlugin*>(data)->OnFocus(focus);
}

void OBSPlugin::OnKeyClickI(void* data, const struct obs_key_event* event, bool key_up)
{
	static_cast<OBSPlugin*>(data)->OnKeyClick(event, key_up);
}

void OBSPlugin::OnFilterRemoveI(void* data, obs_source_t* source)
{
	static_cast<OBSPlugin*>(data)->OnFilterRemove(source);
}

bool OBSPlugin::OnAudioRenderI(void* data, uint64_t* ts_out, obs_source_audio_mix* audio_output, uint32_t mixers, size_t channels, size_t sample_rate)
{
	return static_cast<OBSPlugin*>(data)->OnAudioRender(ts_out, audio_output, mixers, channels, sample_rate);
}

void OBSPlugin::OnTransitionStartI(void* data)
{
	static_cast<OBSPlugin*>(data)->OnTransitionStart();
}
void OBSPlugin::OnTransitionStopI(void* data)
{
	static_cast<OBSPlugin*>(data)->OnTransitionStop();
}
