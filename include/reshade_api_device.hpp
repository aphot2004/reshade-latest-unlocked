/*
 * Copyright (C) 2021 Patrick Mours
 * License: https://github.com/crosire/reshade#license
 */

#pragma once

#include "reshade_api_pipeline.hpp"

namespace reshade { namespace api
{
	/// <summary>
	/// The underlying render API a device is using, as returned by <see cref="device::get_api"/>.
	/// </summary>
	enum class device_api
	{
		/// <summary>Direct3D 9</summary>
		/// <remarks>https://docs.microsoft.com/windows/win32/direct3d9</remarks>
		d3d9 = 0x9000,
		/// <summary>Direct3D 10</summary>
		/// <remarks>https://docs.microsoft.com/windows/win32/direct3d10</remarks>
		d3d10 = 0xa000,
		/// <summary>Direct3D 11</summary>
		/// <remarks>https://docs.microsoft.com/windows/win32/direct3d11</remarks>
		d3d11 = 0xb000,
		/// <summary>Direct3D 12</summary>
		/// <remarks>https://docs.microsoft.com/windows/win32/direct3d12</remarks>
		d3d12 = 0xc000,
		/// <summary>OpenGL</summary>
		/// <remarks>https://www.khronos.org/opengl/</remarks>
		opengl = 0x10000,
		/// <summary>Vulkan</summary>
		/// <remarks>https://www.khronos.org/vulkan/</remarks>
		vulkan = 0x20000
	};

	/// <summary>
	/// The available features a device may support.
	/// </summary>
	enum class device_caps
	{
		/// <summary>
		/// Specifies whether compute shaders are supported.
		/// If this feature is not present, the <see cref="pipeline_stage::compute_shader"/> stage must not be used.
		/// </summary>
		compute_shader = 1,
		/// <summary>
		/// Specifies whether geometry shaders are supported.
		/// If this feature is not present, the <see cref="pipeline_stage::geometry_shader"/>  stage must not be used.
		/// </summary>
		geometry_shader,
		/// <summary>
		/// Specifies whether hull and domain (tessellation) shaders are supported.
		/// If this feature is not present, the <see cref="pipeline_stage::hull_shader"/> and <see cref="pipeline_stage::domain_shader"/> stages must not be used.
		/// </summary>
		hull_and_domain_shader,
		/// <summary>
		/// Specifies whether logic operations are available in the blend state.
		/// If this feature is not present, the <see cref="blend_desc::logic_op_enable"/> and <see cref="blend_desc::logic_op"/> fields are ignored.
		/// </summary>
		logic_op,
		/// <summary>
		/// Specifies whether blend operations which take two sources are supported.
		/// If this feature is not present, <see cref="blend_factor::source1_color"/>, <see cref="blend_factor::one_minus_source1_color"/>, <see cref="blend_factor::source1_alpha"/> and <see cref="blend_factor::one_minus_source1_alpha"/> must not be used.
		/// </summary>
		dual_source_blend,
		/// <summary>
		/// Specifies whether blend state is controlled independently per render target.
		/// If this feature is not present, the blend state settings for all render targets must be identical.
		/// </summary>
		independent_blend,
		/// <summary>
		/// Specifies whether point and wireframe fill modes are supported.
		/// If this feature is not present, <see cref="fill_mode::point"/> and <see cref="fill_mode::wireframe"/> must not be used.
		/// </summary>
		fill_mode_non_solid,
		/// <summary>
		/// Specifies whether conservative rasterization is supported.
		/// If this feature is not present, the <see cref="rasterizer_desc::conservative_rasterization"/> field must be 0.
		/// </summary>
		conservative_rasterization,
		/// <summary>
		/// Specifies whether binding individual render target and depth-stencil resource views is supported.
		/// If this feature is not present, <see cref="command_list::bind_render_targets_and_depth_stencil"/> must not be used (only render passes).
		/// </summary>
		bind_render_targets_and_depth_stencil,
		/// <summary>
		/// Specifies whther more than one viewport is supported.
		/// If this feature is not present, the "first" and "count" parameters to <see cref="command_list::bind_viewports"/> must be 0 and 1.
		/// </summary>
		multi_viewport,
		/// <summary>
		/// Specifies whether partial push constant updates are supported.
		/// If this feature is not present, the "first" parameter to <see cref="command_list::push_constants"/> must be 0 and "count" must cover the entire constant range.
		/// </summary>
		partial_push_constant_updates,
		/// <summary>
		/// Specifies whether partial push descriptor updates are supported.
		/// If this feature is not present, the "first" parameter to <see cref="command_list::push_descriptors"/> must be 0 and "count" must cover the entire descriptor range.
		/// </summary>
		partial_push_descriptor_updates,
		/// <summary>
		/// Specifies whether instancing is supported.
		/// If this feature is not present, the "instance_count" and "first_instance" parameters to <see cref="command_list::draw"/> and <see cref="command_list::draw_indexed"/> must be 1 and 0.
		/// </summary>
		draw_instanced,
		/// <summary>
		/// Specifies whether indirect draw or dispatch calls are supported.
		/// If this feature is not present, <see cref="command_list::draw_or_dispatch_indirect"/> must not be used.
		/// </summary>
		draw_or_dispatch_indirect,
		/// <summary>
		/// Specifies whether copying between buffers is supported.
		/// If this feature is not present, <see cref="command_list::copy_buffer_region"/> must not be used.
		/// </summary>
		copy_buffer_region,
		/// <summary>
		/// Specifies whether copying between buffers and textures is supported.
		/// If this feature is not present, <see cref="command_list::copy_buffer_to_texture"/> and <see cref="command_list::copy_texture_to_buffer"/> must not be used.
		/// </summary>
		copy_buffer_to_texture,
		/// <summary>
		/// Specifies whether blitting between resources is supported.
		/// If this feature is not present, the "source_box" and "dest_box" parameters to <see cref="command_list::copy_texture_region"/> must have the same dimensions.
		/// </summary>
		blit,
		/// <summary>
		/// Specifies whether resolving a region of a resource rather than its entirety is supported.
		/// If this feature is not present, the "source_box" and "dest_offset" parameters to <see cref="command_list::resolve_texture_region"/> must be <see langword="nullptr"/>.
		/// </summary>
		resolve_region,
		/// <summary>
		/// Specifies whether copying query results to a buffer is supported.
		/// If this feature is not present, <see cref="command_list::copy_query_pool_results"/> must not be used.
		/// </summary>
		copy_query_pool_results,
		/// <summary>
		/// Specifies whether comparison sampling is supported.
		/// If this feature is not present, the <see cref="sampler_desc::compare_op"/> field is ignored and the compare filter types have no effect.
		/// </summary>
		sampler_compare,
		/// <summary>
		/// Specifies whether anisotropic filtering is supported.
		/// If this feature is not present, <see cref="filter_mode::anisotropic"/> must not be used.
		/// </summary>
		sampler_anisotropic,
		/// <summary>
		/// Specifies whether combined sampler and resource view descriptors are supported.
		/// If this feature is not present, <see cref="descriptor_type::sampler_with_resource_view"/> must not be used.
		/// </summary>
		sampler_with_resource_view,
	};

	/// <summary>
	/// The base class for objects provided by the ReShade API.
	/// <para>This lets you store and retrieve custom data with objects, e.g. to be able to communicate persistent information between event callbacks.</para>
	/// </summary>
	class __declspec(novtable) api_object
	{
	public:
		/// <summary>
		/// Gets a user-defined 64-bit value from the object that was previously set via <see cref="set_private_data"/>, or zero if none associated with the specified <paramref name="guid"/> exists.
		/// </summary>
		virtual void get_private_data(const uint8_t guid[16], uint64_t *data) const = 0;
		/// <summary>
		/// Stores a user-defined 64-bit value in the object and associates it with the specified <paramref name="guid"/>.
		/// </summary>
		/// <remarks>
		/// This function may NOT be called concurrently from multiple threads!
		/// </remarks>
		virtual void set_private_data(const uint8_t guid[16], const uint64_t data)  = 0;

		/// <summary>
		/// Gets the underlying native object for this API object.
		/// </summary>
		/// <remarks>
		/// For <see cref="device"/> this will be be a pointer to a 'IDirect3DDevice9', 'ID3D10Device', 'ID3D11Device' or 'ID3D12Device' object or a 'HGLRC' or 'VkDevice' handle.<br/>
		/// For <see cref="command_list"/> this will be a pointer to a 'ID3D11DeviceContext' (when recording), 'ID3D11CommandList' (when executing) or 'ID3D12GraphicsCommandList' object or a 'VkCommandBuffer' handle.<br/>
		/// For <see cref="command_queue"/> this will be a pointer to a 'ID3D11DeviceContext' or 'ID3D12CommandQueue' object or a 'VkQueue' handle.<br/>
		/// For <see cref="effect_runtime"/> this will be a pointer to a 'IDirect3DSwapChain9' or 'IDXGISwapChain' object or a 'HDC' or 'VkSwapchainKHR' handle.
		/// </remarks>
		virtual uint64_t get_native_object() const = 0;

		/// <summary>
		/// Gets a reference to user-defined data from the object that was previously allocated via <see cref="create_private_data"/>.
		/// </summary>
		template <typename T> inline T &get_private_data(const uint8_t guid[16])
		{
			uint64_t res;
			get_private_data(guid, &res);
			return *reinterpret_cast<T *>(static_cast<uintptr_t>(res));
		}
		/// <summary>
		/// Allocates user-defined data and stores it in the object.
		/// </summary>
		template <typename T> inline T &create_private_data(const uint8_t guid[16])
		{
			uint64_t res = reinterpret_cast<uintptr_t>(new T());
			set_private_data(guid,  res);
			return *reinterpret_cast<T *>(static_cast<uintptr_t>(res));
		}
		/// <summary>
		/// Frees user-defined data that was previously allocated via <see cref="create_private_data"/>.
		/// </summary>
		template <typename T> inline void destroy_private_data(const uint8_t guid[16])
		{
			uint64_t res;
			get_private_data(guid, &res);
			delete  reinterpret_cast<T *>(static_cast<uintptr_t>(res));
			set_private_data(guid, 0);
		}
	};

	/// <summary>
	/// A logical render device, used for resource creation and global operations.
	/// <para>Functionally equivalent to a 'IDirect3DDevice9', 'ID3D10Device', 'ID3D11Device', 'ID3D12Device', 'HGLRC' or 'VkDevice'.</para>
	/// </summary>
	/// <remarks>
	/// This class is safe to use concurrently from multiple threads in D3D10+ and Vulkan (with the exception of <see cref="device::wait_idle"/>).
	/// </remarks>
	class __declspec(novtable) device : public api_object
	{
	public:
		/// <summary>
		/// Gets the underlying render API used by this device.
		/// </summary>
		virtual device_api get_api() const = 0;

		/// <summary>
		/// Checks whether the device supports the specified <paramref name="capability"/>.
		/// </summary>
		virtual bool check_capability(device_caps capability) const = 0;
		/// <summary>
		/// Checks whether the specified texture <paramref name="format"/> supports the specified <paramref name="usage"/>.
		/// </summary>
		virtual bool check_format_support(format format, resource_usage usage) const = 0;

		/// <summary>
		/// Creates a new sampler state object.
		/// </summary>
		/// <param name="desc">Description of the sampler to create.</param>
		/// <param name="out_handle">Pointer to a variable that is set to the handle of the created sampler.</param>
		/// <returns><see langword="true"/> if the sampler was successfully created, <see langword="false"/> otherwise (in this case <paramref name="out_handle"/> is set to zero).</returns>
		virtual bool create_sampler(const sampler_desc &desc, sampler *out_handle) = 0;
		/// <summary>
		/// Instantly destroys a sampler that was previously created via <see cref="create_sampler"/>.
		/// </summary>
		virtual void destroy_sampler(sampler handle) = 0;

		/// <summary>
		/// Allocates and creates a new resource.
		/// </summary>
		/// <param name="desc">Description of the resource to create.</param>
		/// <param name="initial_data">Optional data to upload to the resource after creation. This should point to an array of <see cref="mapped_subresource"/>, one for each subresource (mipmap levels and array layers). Can be <see langword="nullptr"/> to indicate no initial data to upload.</param>
		/// <param name="initial_state">Initial state of the resource after creation. This can later be changed via <see cref="command_list::barrier"/>.</param>
		/// <param name="out_handle">Pointer to a variable that is set to the handle of the created resource.</param>
		/// <returns><see langword="true"/> if the resource was successfully created, <see langword="false"/> otherwise (in this case <paramref name="out_handle"/> is set to zero).</returns>
		virtual bool create_resource(const resource_desc &desc, const subresource_data *initial_data, resource_usage initial_state, resource *out_handle) = 0;
		/// <summary>
		/// Instantly destroys a resource that was previously created via <see cref="create_resource"/> and frees its memory.
		/// Make sure the resource is no longer in use on the GPU (via any command list that may reference it and is still being executed) before doing this and never try to destroy resources created by the application!
		/// </summary>
		virtual void destroy_resource(resource handle) = 0;

		/// <summary>
		/// Gets the description of the specified <paramref name="resource"/>.
		/// </summary>
		virtual resource_desc get_resource_desc(resource resource) const = 0;

		/// <summary>
		/// Associates a name with a resource, for easier debugging in external tools.
		/// </summary>
		/// <param name="handle">Resource to associate a name with.</param>
		/// <param name="name">A null-terminated name string.</param>
		virtual void set_resource_name(resource handle, const char *name) = 0;

		/// <summary>
		/// Creates a new resource view for the specified <paramref name="resource"/>.
		/// </summary>
		/// <param name="resource">Resource to create the view to.</param>
		/// <param name="usage_type">Usage type of the resource view to create. Set to <see cref="resource_usage::shader_resource"/> to create a shader resource view, <see cref="resource_usage::depth_stencil"/> for a depth-stencil view, <see cref="resource_usage::render_target"/> for a render target etc.</param>
		/// <param name="desc">Description of the resource view to create.</param>
		/// <param name="out_handle">Pointer to a variable that is set to the handle of the created resource view.</param>
		/// <returns><see langword="true"/> if the resource view was successfully created, <see langword="false"/> otherwise (in this case <paramref name="out_handle"/> is set to zero).</returns>
		virtual bool create_resource_view(resource resource, resource_usage usage_type, const resource_view_desc &desc, resource_view *out_handle) = 0;
		/// <summary>
		/// Instantly destroys a resource view that was previously created via <see cref="create_resource_view"/>.
		/// </summary>
		virtual void destroy_resource_view(resource_view handle) = 0;

		/// <summary>
		/// Gets the handle to the underlying resource the specified resource <paramref name="view"/> was created for.
		/// </summary>
		virtual resource get_resource_from_view(resource_view view) const = 0;
		/// <summary>
		/// Gets the description of the specified resource <paramref name="view"/>.
		/// </summary>
		virtual resource_view_desc get_resource_view_desc(resource_view view) const = 0;

		/// <summary>
		/// Associates a name with a resource view, for easier debugging in external tools.
		/// </summary>
		/// <param name="handle">Resource view to associate a name with.</param>
		/// <param name="name">A null-terminated name string.</param>
		virtual void set_resource_view_name(resource_view handle, const char *name) = 0;

		/// <summary>
		/// Creates a new pipeline state object.
		/// </summary>
		/// <param name="desc">Description of the pipeline state object to create.</param>
		/// <param name="dynamic_state_count">Number of dynamic pipeline states.</param>
		/// <param name="dynamic_states">Optional pointer to an array of pipeline states that may be dynamically updated via <see cref="command_list::bind_pipeline_states"/> after binding the created pipeline state object.</param>
		/// <param name="out_handle">Pointer to a variable that is set to the handle of the created pipeline state object.</param>
		/// <returns><see langword="true"/> if the pipeline state object was successfully created, <see langword="false"/> otherwise (in this case <paramref name="out_handle"/> is set to zero).</returns>
		virtual bool create_pipeline(const pipeline_desc &desc, uint32_t dynamic_state_count, const dynamic_state *dynamic_states, pipeline *out_handle) = 0;
		/// <summary>
		/// Instantly destroys a pipeline state object that was previously created via <see cref="create_pipeline"/>.
		/// </summary>
		virtual void destroy_pipeline(pipeline handle) = 0;

		/// <summary>
		/// Creates a new render pass.
		/// </summary>
		/// <param name="attachment_count">Number of attachments to add to the render pass.</param>
		/// <param name="attachments">Pointer to an array of attachments to add to the render pass.</param>
		/// <param name="out_handle">Pointer to a variable that is set to the handle of the created render pass.</param>
		/// <returns><see langword="true"/> if the render pass was successfully created, <see langword="false"/> otherwise (in this case <paramref name="out_handle"/> is set to zero).</returns>
		virtual bool create_render_pass(uint32_t attachment_count, const attachment_desc *attachments, render_pass *out_handle) = 0;
		/// <summary>
		/// Instantly destroys a render pass that was previously created via <see cref="create_render_pass"/>.
		/// </summary>
		virtual void destroy_render_pass(render_pass handle) = 0;

		/// <summary>
		/// Creates a new framebuffer.
		/// </summary>
		/// <param name="render_pass_template">Render pass to use as template to figure out where to bind attachments.</param>
		/// <param name="attachment_count">Number of resource views to bind to the framebuffer.</param>
		/// <param name="attachments">Pointer to an array of resource views to bind to the framebuffer.</param>
		/// <param name="out_handle">Pointer to a variable that is set to the handle of the created framebuffer.</param>
		/// <returns><see langword="true"/> if the framebuffer was successfully created, <see langword="false"/> otherwise (in this case <paramref name="out_handle"/> is set to zero).</returns>
		virtual bool create_framebuffer(render_pass render_pass_template, uint32_t attachment_count, const resource_view *attachments, framebuffer *out_handle) = 0;
		/// <summary>
		/// Instantly destroys a framebuffer that was previously created via <see cref="create_framebuffer"/>.
		/// </summary>
		virtual void destroy_framebuffer(framebuffer handle) = 0;

		/// <summary>
		/// Gets the handle to the resource view of the specfied <paramref name="type"/> in the <paramref name="framebuffer"/> object.
		/// </summary>
		/// <param name="framebuffer">Framebuffer object to get the resource view from.</param>
		/// <param name="type">Type of the attachment to get.</param>
		/// <param name="index">Index of the attachment of the specified <paramref name="type"/> to get.</param>
		/// <returns>Handle of the attached resource view if the attachment of the specified <paramref name="type"/> and <paramref name="index"/> exists in the framebuffer, zero otherwise.</returns>
		virtual resource_view get_framebuffer_attachment(framebuffer framebuffer, attachment_type type, uint32_t index) const = 0;

		/// <summary>
		/// Creates a new pipeline layout.
		/// </summary>
		/// <param name="param_count">Number of layout parameters.</param>
		/// <param name="params">Pointer to an array of layout parameters that describe this pipeline layout.</param>
		/// <param name="out_handle">Pointer to a variable that is set to the handle of the created pipeline layout.</param>
		/// <returns><see langword="true"/> if the pipeline layout was successfully created, <see langword="false"/> otherwise (in this case <paramref name="out_handle"/> is set to zero).</returns>
		virtual bool create_pipeline_layout(uint32_t param_count, const pipeline_layout_param *params, pipeline_layout *out_handle) = 0;
		/// <summary>
		/// Instantly destroys a pipeline layout that was previously created via <see cref="create_pipeline_layout"/>.
		/// </summary>
		virtual void destroy_pipeline_layout(pipeline_layout handle) = 0;

		/// <summary>
		/// Gets a layout parameter from the specified pipeline <paramref name="layout"/>.
		/// </summary>
		/// <param name="layout">Pipeline layout to get the layout parameter from.</param>
		/// <param name="index">Index of the layout parameter to get.</param>
		virtual pipeline_layout_param get_pipeline_layout_param(pipeline_layout layout, uint32_t index) const = 0;

		/// <summary>
		/// Creates a new descriptor set layout.
		/// </summary>
		/// <param name="range_count">Number of descriptor ranges.</param>
		/// <param name="ranges">Pointer to an array of descriptor ranges that describe this descriptor set layout.</param>
		/// <param name="push_descriptors"><see langword="true"/> if this layout is later used with <see cref="command_list::push_descriptors"/>, <see langword="false"/> if not.</param>
		/// <param name="out_handle">Pointer to a variable that is set to the handle of the created descriptor set layout.</param>
		/// <returns><see langword="true"/> if the descriptor set layout was successfully created, <see langword="false"/> otherwise (in this case <paramref name="out_handle"/> is set to zero).</returns>
		virtual bool create_descriptor_set_layout(uint32_t range_count, const descriptor_range *ranges, bool push_descriptors, descriptor_set_layout *out_handle) = 0;
		/// <summary>
		/// Instantly destroys a descriptor set layout that was previously created via <see cref="create_descriptor_set_layout"/>.
		/// </summary>
		virtual void destroy_descriptor_set_layout(descriptor_set_layout handle) = 0;

		/// <summary>
		/// Gets the descriptor of the specified descriptor set <paramref name="layout"/>.
		/// </summary>
		/// <remarks>
		/// Call this first with <paramref name="out_ranges"/> set to <see langword="nullptr"/> to get the size of the array in <paramref name="out_count"/>, then allocate the array and call this again with <paramref name="out_ranges"/> set to it.
		/// </remarks>
		/// <param name="layout">Pipeline layout to get the description from.</param>
		/// <param name="out_count">Pointer to a variable that is set to the number of descriptor ranges in the <paramref name="layout"/>.</param>
		/// <param name="out_ranges">Optional pointer to an array that is filled with the descriptor ranges in the <paramref name="layout"/>.</param>
		virtual void get_descriptor_set_layout_ranges(descriptor_set_layout layout, uint32_t *out_count, descriptor_range *out_ranges) const = 0;

		/// <summary>
		/// Creates a new query pool.
		/// </summary>
		/// <param name="type">Type of queries that will be used with this pool.</param>
		/// <param name="size">Number of queries to allocate in the pool.</param>
		/// <param name="out_handle">Pointer to a variable that is set to the handle of the created query pool.</param>
		/// <returns><see langword="true"/> if the query pool was successfully created, <see langword="false"/> otherwise (in this case <paramref name="out_handle"/> is set to zero).</returns>
		virtual bool create_query_pool(query_type type, uint32_t size, query_pool *out_handle) = 0;
		/// <summary>
		/// Instantly destroys a query pool that was previously created via <see cref="create_query_pool"/>.
		/// </summary>
		virtual void destroy_query_pool(query_pool handle) = 0;

		/// <summary>
		/// Allocates one or more descriptor sets from an internal pool.
		/// </summary>
		/// <param name="count">Number of descriptor sets to allocate.</param>
		/// <param name="layouts">Pointer to an array of layouts to allocate the descriptor sets with.</param>
		/// <param name="out_sets">Pointer to an array of handles with at least <paramref name="count"/> elements that is filled with the handles of the created descriptor sets.</param>
		/// <returns><see langword="true"/> if the descriptor sets were successfully created, <see langword="false"/> otherwise (in this case <paramref name="out"/> is filles with zeroes).</returns>
		virtual bool create_descriptor_sets(uint32_t count, const descriptor_set_layout *layouts, descriptor_set *out_sets) = 0;
		/// <summary>
		/// Frees one or more descriptor sets that were previously allocated via <see cref="create_descriptor_sets"/>.
		/// </summary>
		virtual void destroy_descriptor_sets(uint32_t count, const descriptor_set *sets) = 0;

		/// <summary>
		/// Gets the offset (in descriptors) of the specified descriptor <paramref name="set"/> in the underlying pool.
		/// </summary>
		/// <param name="set">Descriptor set to get the offset from.</param>
		/// <param name="out_pool">Pointer to a variable that is set to the handle of the underlying descriptor pool the <paramref name="set"/> was allocated from.</param>
		/// <param name="out_offset">Pointer to a variable that is set to the offset of the descriptor set in the underlying pool.</param>
		virtual void get_descriptor_pool_offset(descriptor_set set, descriptor_pool *out_pool, uint32_t *out_offset) const = 0;

		/// <summary>
		/// Maps the memory of a buffer resource into application address space.
		/// </summary>
		/// <param name="resource">Buffer resource to map to host memory.</param>
		/// <param name="offset">Offset (in bytes) into the buffer resource to start mapping.</param>
		/// <param name="size">Number of bytes to map. Set to -1 (0xFFFFFFFFFFFFFFFF) to indicate that the entire buffer should be mapped.</param>
		/// <param name="access">A hint on how the returned data pointer will be accessed.</param>
		/// <param name="out_data">Pointer to a variable that is set to a pointer to the memory of the buffer resource.</param>
		/// <returns><see langword="true"/> if the memory of the buffer resource was successfully mapped, <see langword="false"/> otherwise (in this case <paramref name="out_data"/> is set to <see langword="nullptr"/>).</returns>
		virtual bool map_buffer_region(resource resource, uint64_t offset, uint64_t size, map_access access, void **out_data) = 0;
		/// <summary>
		/// Unmaps a previously mapped buffer resource.
		/// </summary>
		/// <param name="resource">Buffer resource to unmap from host memory.</param>
		virtual void unmap_buffer_region(resource resource) = 0;
		/// <summary>
		/// Maps the memory of a texture resource into application address space.
		/// </summary>
		/// <param name="resource">Texture resource to map to host memory.</param>
		/// <param name="subresource">Index of the subresource to map (<c>level + (layer * levels)</c>).</param>
		/// <param name="box">An optional 3D box (or <see langword="nullptr"/> to reference the entire subresource) that defines the region in the <paramref name="resource"/> to map, in the format <c>{ left, top, front, right, bottom, back }</c>.</param>
		/// <param name="access">A hint on how the returned data pointer will be accessed.</param>
		/// <param name="out_data">Pointer to a variable that is set to a pointer to the memory of the texture resource and optionally the row and slice pitch of that data (depending on the resource type).</param>
		/// <returns><see langword="true"/> if the memory of the texture resource was successfully mapped, <see langword="false"/> otherwise (in this case <paramref name="out_data"/> is set to <see langword="nullptr"/>).</returns>
		virtual bool map_texture_region(resource resource, uint32_t subresource, const int32_t box[6], map_access access, subresource_data *out_data) = 0;
		/// <summary>
		/// Unmaps a previously mapped texture resource.
		/// </summary>
		/// <param name="resource">Texture resource to unmap from host memory.</param>
		/// <param name="subresource">Index of the subresource to unmap (<c>level + (layer * levels)</c>).</param>
		virtual void unmap_texture_region(resource resource, uint32_t subresource) = 0;

		/// <summary>
		/// Uploads data to a buffer resource.
		/// </summary>
		/// <param name="data">Pointer to the data to upload.</param>
		/// <param name="resource">Buffer resource to upload to.</param>
		/// <param name="offset">Offset (in bytes) into the buffer resource to start uploading to.</param>
		/// <param name="size">Number of bytes to upload.</param>
		virtual void update_buffer_region(const void *data, resource resource, uint64_t offset, uint64_t size) = 0;
		/// <summary>
		/// Uploads data to a texture resource.
		/// </summary>
		/// <param name="data">Pointer to the data to upload.</param>
		/// <param name="resource">Texture resource to upload to.</param>
		/// <param name="subresource">Index of the subresource to upload to (<c>level + (layer * levels)</c>).</param>
		/// <param name="box">An optional 3D box (or <see langword="nullptr"/> to reference the entire subresource) that defines the region in the <paramref name="resource"/> to upload to, in the format <c>{ left, top, front, right, bottom, back }</c>.</param>
		virtual void update_texture_region(const subresource_data &data, resource resource, uint32_t subresource, const int32_t box[6] = nullptr) = 0;

		/// <summary>
		/// Updates the contents of descriptor sets with the specified descriptors.
		/// </summary>
		/// <param name="count">Number of <paramref name="updates"/> to process.</param>
		/// <param name="updates">Pointer to an array of descriptor set updates to process.</param>
		virtual void update_descriptor_sets(uint32_t count, const descriptor_set_update *updates) = 0;

		/// <summary>
		/// Gets the results of queries in a query pool.
		/// </summary>
		/// <param name="pool">Query pool that contains the queries.</param>
		/// <param name="first">Index of the first query in the pool to copy the results from.</param>
		/// <param name="count">Number of query results to copy.</param>
		/// <param name="results">Pointer to an array that is filled with the results.</param>
		/// <param name="stride">Size (in bytes) of each element in the <paramref name="results"/> array.</param>
		/// <returns><see langword="true"/> if the query results were successfully downloaded from the GPU, <see langword="false"/> otherwise.</returns>
		virtual bool get_query_pool_results(query_pool pool, uint32_t first, uint32_t count, void *results, uint32_t stride) = 0;

		/// <summary>
		/// Waits for all issued GPU operations to finish before returning.
		/// This can be used to e.g. ensure that resources are no longer in use on the GPU before destroying them.
		/// </summary>
		/// <remarks>
		/// Must not be called while another thread is recording to the immediate command list!
		/// </remarks>
		virtual void wait_idle() const = 0;
	};

	/// <summary>
	/// The base class for objects that are children to a logical render <see cref="device"/>.
	/// </summary>
	class __declspec(novtable) device_object : public api_object
	{
	public:
		/// <summary>
		/// Gets the parent device for this object.
		/// </summary>
		virtual device *get_device() = 0;
	};

	/// <summary>
	/// A swap chain, used to present images to the screen.
	/// <para>Functionally equivalent to a 'IDirect3DSwapChain9', 'IDXGISwapChain', 'HDC' or 'VkSwapchainKHR'.</para>
	/// </summary>
	class __declspec(novtable) swapchain : public device_object
	{
	public:
		/// <summary>
		/// Gets the back buffer resource at the specified <paramref name="index"/> in this swap chain.
		/// </summary>
		/// <param name="index">Index of the back buffer. This has to be between zero and the value returned by <see cref="get_back_buffer_count"/>.</param>
		virtual resource get_back_buffer(uint32_t index) = 0;
		/// <summary>
		/// Gets the number of back buffer resources in this swap chain.
		/// </summary>
		virtual uint32_t get_back_buffer_count() const = 0;

		/// <summary>
		/// Gets the current back buffer resource.
		/// </summary>
		inline  resource get_current_back_buffer() { return get_back_buffer(get_current_back_buffer_index()); }
		/// <summary>
		/// Gets the index of the back buffer resource that can currently be rendered into.
		/// </summary>
		virtual uint32_t get_current_back_buffer_index() const = 0;

		/// <summary>
		/// Gets the effect runtime associated with this swap chain.
		/// </summary>
		inline  class effect_runtime *get_effect_runtime() { return reinterpret_cast<effect_runtime *>(this); }
	};

	/// <summary>
	/// A command list, used to enqueue render commands on the CPU, before later executing them in a command queue.
	/// <para>Functionally equivalent to a 'ID3D11CommandList', 'ID3D12CommandList' or 'VkCommandBuffer'.</para>
	/// </summary>
	/// <remarks>
	/// This class may NOT be used concurrently from multiple threads!
	/// </remarks>
	class __declspec(novtable) command_list : public device_object
	{
	public:
		/// <summary>
		/// Adds a barrier for the specified <paramref name="resource"/> to the command stream.
		/// When both <paramref name="old_state"/> and <paramref name="new_state"/> are <see cref="resource_usage::unordered_access"/> a UAV barrier is added, otherwise a state transition is performed.
		/// </summary>
		/// <param name="resource">Resource to transition.</param>
		/// <param name="old_state">Usage flags describing how the <paramref name="resource"/> was used before this barrier.</param>
		/// <param name="new_state">Usage flags describing how the <paramref name="resource"/> will be used after this barrier.</param>
		inline  void barrier(resource resource, resource_usage old_state, resource_usage new_state) { barrier(1, &resource, &old_state, &new_state); }
		/// <summary>
		/// Adds a barrier for the specified <paramref name="resources"/> to the command stream.
		/// </summary>
		/// <param name="count">Number of resources to transition.</param>
		/// <param name="resources">Pointer to an array of resources to transition.</param>
		/// <param name="old_states">Pointer to an array of usage flags describing how the <paramref name="resources"/> were used before this barrier.</param>
		/// <param name="new_states">Pointer to an array of usage flags describing how the <paramref name="resources"/> will be used after this barrier.</param>
		virtual void barrier(uint32_t count, const resource *resources, const resource_usage *old_states, const resource_usage *new_states) = 0;

		/// <summary>
		/// Begins a render pass by binding its render targets and depth-stencil buffer.
		/// </summary>
		/// <param name="pass">Render pass to begin.</param>
		/// <param name="framebuffer">Framebuffer to bind.</param>
		/// <param name="clear_value_count">Number of clear values, or zero if there are no attachments with the <see cref="attachment_load_op::clear"/> operation in the render pass.</param>
		/// <param name="clear_values">Pointer to an array of clear values, with four 32-bit elements for each attachment in the framebuffer.</param>
		virtual void begin_render_pass(render_pass pass, framebuffer framebuffer, uint32_t clear_value_count = 0, const void *clear_values = nullptr) = 0;
		/// <summary>
		/// Ends a render pass.
		/// This must be preceeded by a call to <see cref="begin_render_pass"/>.
		/// Render passes cannot be nested.
		/// </summary>
		virtual void end_render_pass() = 0;
		/// <summary>
		/// Binds individual render target and depth-stencil resource views.
		/// This must not be called between <see cref="begin_render_pass"/> and <see cref="end_render_pass"/>.
		/// </summary>
		/// <remarks>
		/// This is not supported (and will do nothing) in Vulkan.
		/// </remarks>
		/// <param name="count">Number of render target views to bind.</param>
		/// <param name="rtvs">Pointer to an array of render target views to bind.</param>
		/// <param name="dsv">Depth-stencil view to bind, or zero to bind none.</param>
		virtual void bind_render_targets_and_depth_stencil(uint32_t count, const resource_view *rtvs, resource_view dsv = { 0 }) = 0;

		/// <summary>
		/// Binds a pipeline state object.
		/// </summary>
		/// <param name="type">Pipeline stage to bind the pipeline state object to.</param>
		/// <param name="pipeline">Pipeline state object to bind.</param>
		virtual void bind_pipeline(pipeline_stage type, pipeline pipeline) = 0;
		/// <summary>
		/// Updates the specfified pipeline <paramref name="state"/> to the specified <paramref name="value"/>.
		/// This is only valid for states that have been listed in the dynamic states provided at creation of the currently bound pipeline state object.
		/// </summary>
		/// <param name="state">Pipeline state to update.</param>
		/// <param name="value">Value to update the pipeline state to.</param>
		inline  void bind_pipeline_state(dynamic_state state, uint32_t value) { bind_pipeline_states(1, &state, &value); }
		/// <summary>
		/// Updates the specfified pipeline <paramref name="states"/> to the specified <paramref name="values"/>.
		/// This is only valid for states that have been listed in the dynamic states provided at creation of the currently bound pipeline state object.
		/// </summary>
		/// <param name="count">Number of pipeline states to update.</param>
		/// <param name="states">Pointer to an array of pipeline states to update.</param>
		/// <param name="values">Pointer to an array of values to update the pipeline states to, with one for each state in <paramref name="states"/>.</param>
		virtual void bind_pipeline_states(uint32_t count, const dynamic_state *states, const uint32_t *values) = 0;
		/// <summary>
		/// Binds an array of viewports to the rasterizer stage.
		/// </summary>
		/// <param name="first">Index of the first viewport to bind. In D3D9, D3D10, D3D11 and D3D12 this has to be 0.</param>
		/// <param name="count">Number of viewports to bind. In D3D9 this has to be 1.</param>
		/// <param name="viewports">Pointer to an array of viewports in the format <c>{ x 0, y 0, width 0, height 0, min depth 0, max depth 0, x 1, y 1, width 1, height 1, ... }</c>.</param>
		virtual void bind_viewports(uint32_t first, uint32_t count, const float *viewports) = 0;
		/// <summary>
		/// Binds an array of scissor rectangles to the rasterizer stage.
		/// </summary>
		/// <param name="first">Index of the first scissor rectangle to bind. In D3D9, D3D10, D3D11 and D3D12 this has to be 0.</param>
		/// <param name="count">Number of scissor rectangles to bind. In D3D9 this has to be 1.</param>
		/// <param name="rects">Pointer to an array of scissor rectangles in the format <c>{ left 0, top 0, right 0, bottom 0, left 1, top 1, right 1, ... }</c>.</param>
		virtual void bind_scissor_rects(uint32_t first, uint32_t count, const int32_t *rects) = 0;

		/// <summary>
		/// Directly updates constant values in the specified shader pipeline stages.
		/// <para>In D3D9 this updates the values of uniform registers, in D3D10/11 and OpenGL the constant buffer specified in the pipeline layout, in D3D12 it sets root constants and in Vulkan push constants.</para>
		/// </summary>
		/// <param name="stages">Shader stages that will use the updated constants.</param>
		/// <param name="layout">Pipeline layout that describes where the constants are located.</param>
		/// <param name="param">Layout parameter index of the constant range in the pipeline <paramref name="layout"/> (root parameter index in D3D12).</param>
		/// <param name="first">Start offset (in 32-bit values) to the first constant in the constant range to begin updating.</param>
		/// <param name="count">Number of 32-bit values to update.</param>
		/// <param name="values">Pointer to an array of 32-bit values to set the constants to. These can be floating-point, integer or boolean depending on what the shader is expecting.</param>
		virtual void push_constants(shader_stage stages, pipeline_layout layout, uint32_t param, uint32_t first, uint32_t count, const void *values) = 0;
		/// <summary>
		/// Directly binds a temporary descriptor set for the specfified shader pipeline stage and updates with an array of descriptors.
		/// </summary>
		/// <param name="stages">Shader stages that will use the updated descriptors.</param>
		/// <param name="layout">Pipeline layout that describes the descriptors.</param>
		/// <param name="param">Layout parameter index of the descriptor set in the pipeline <paramref name="layout"/> (root parameter index in D3D12, descriptor set index in Vulkan).</param>
		/// <param name="update">Range of descriptors to update in the temporary set (<see cref="descriptor_set_update::set"/> is ignored).</param>
		virtual void push_descriptors(shader_stage stages, pipeline_layout layout, uint32_t param, const descriptor_set_update &update) = 0;
		/// <summary>
		/// Binds a single descriptor set.
		/// </summary>
		/// <param name="stages">Shader stages that will use the descriptors.</param>
		/// <param name="layout">Pipeline layout that describes the descriptors.</param>
		/// <param name="param">Layout parameter index of the descriptor set in the pipeline <paramref name="layout"/> (root parameter index in D3D12, descriptor set index in Vulkan).</param>
		/// <param name="set">Descriptor set to bind.</param>
		inline  void bind_descriptor_set(shader_stage stages, pipeline_layout layout, uint32_t param, descriptor_set set) { bind_descriptor_sets(stages, layout, param, 1, &set); }
		/// <summary>
		/// Binds an array of descriptor sets.
		/// </summary>
		/// <param name="stages">Shader stages that will use the descriptors.</param>
		/// <param name="layout">Pipeline layout that describes the descriptors.</param>
		/// <param name="first">Layout parameter index of the first descriptor set to bind.</param>
		/// <param name="count">Number of descriptor sets to bind.</param>
		/// <param name="sets">Pointer to an array of descriptor sets to bind.</param>
		virtual void bind_descriptor_sets(shader_stage stages, pipeline_layout layout, uint32_t first, uint32_t count, const descriptor_set *sets) = 0;

		/// <summary>
		/// Binds an index buffer to the input-assembler stage.
		/// </summary>
		/// <param name="buffer">Index buffer resource. This resource must have been created with the <see cref="resource_usage::index_buffer"/> usage.</param>
		/// <param name="offset">Offset (in bytes) from the start of the index buffer to the first index to use. In D3D9 this has to be 0.</param>
		/// <param name="index_size">Size (in bytes) of each index. Can typically be 2 (16-bit indices) or 4 (32-bit indices).</param>
		virtual void bind_index_buffer(resource buffer, uint64_t offset, uint32_t index_size) = 0;
		/// <summary>
		/// Binds a single vertex buffer to the input-assembler stage.
		/// </summary>
		/// <param name="index">Input slot for binding.</param>
		/// <param name="buffer">Vertex buffer resource. This resources must have been created with the <see cref="resource_usage::vertex_buffer"/> usage.</param>
		/// <param name="offset">Offset (in bytes) from the start of the vertex buffer to the first vertex element to use.</param>
		/// <param name="stride">Size (in bytes) of the vertex element that will be used from the vertex buffer (is added to an element offset to advance to the next).</param>
		inline  void bind_vertex_buffer(uint32_t index, resource buffer, uint64_t offset, uint32_t stride) { bind_vertex_buffers(index, 1, &buffer, &offset, &stride); }
		/// <summary>
		/// Binds an array of vertex buffers to the input-assembler stage.
		/// </summary>
		/// <param name="first">First input slot for binding.</param>
		/// <param name="count">Number of vertex buffers to bind.</param>
		/// <param name="buffers">Pointer to an array of vertex buffer resources. These resources must have been created with the <see cref="resource_usage::vertex_buffer"/> usage.</param>
		/// <param name="offsets">Pointer to an array of offset values, with one for each buffer in <paramref name="buffers"/>. Each offset is the number of bytes from the start of the vertex buffer to the first vertex element to use.</param>
		/// <param name="strides">Pointer to an array of stride values, with one for each buffer in <paramref name="strides"/>. Each stride is the size (in bytes) of the vertex element that will be used from that vertex buffer (is added to an element offset to advance to the next).</param>
		virtual void bind_vertex_buffers(uint32_t first, uint32_t count, const resource *buffers, const uint64_t *offsets, const uint32_t *strides) = 0;

		/// <summary>
		/// Draws non-indexed primitives.
		/// </summary>
		/// <param name="vertex_count">Number of vertices to draw.</param>
		/// <param name="instance_count">Number of instances to draw. In D3D9 this has to be 1.</param>
		/// <param name="first_vertex">Index of the first vertex.</param>
		/// <param name="first_instance">A value added to each index before reading per-instance data from a vertex buffer. In D3D9 this has to be 0.</param>
		virtual void draw(uint32_t vertex_count, uint32_t instance_count, uint32_t first_vertex, uint32_t first_instance) = 0;
		/// <summary>
		/// Draws indexed primitives.
		/// </summary>
		/// <param name="index_count">Number of indices read from the index buffer for each instance.</param>
		/// <param name="instance_count">Number of instances to draw. In D3D9 this has to be 1.</param>
		/// <param name="first_index">The location of the first index read from the index buffer.</param>
		/// <param name="vertex_offset">A value added to each index before reading per-vertex data from a vertex buffer.</param>
		/// <param name="first_instance">A value added to each index before reading per-instance data from a vertex buffer. In D3D9 this has to be 0.</param>
		virtual void draw_indexed(uint32_t index_count, uint32_t instance_count, uint32_t first_index, int32_t vertex_offset, uint32_t first_instance) = 0;
		/// <summary>
		/// Performs a compute shader dispatch.
		/// </summary>
		/// <remarks>
		/// This is not supported (and will do nothing) in D3D9 and D3D10.
		/// </remarks>
		/// <param name="group_count_x">Number of thread groups dispatched in the x direction.</param>
		/// <param name="group_count_y">Number of thread groups dispatched in the y direction.</param>
		/// <param name="group_count_z">Number of thread groups dispatched in the z direction.</param>
		virtual void dispatch(uint32_t group_count_x, uint32_t group_count_y, uint32_t group_count_z) = 0;
		/// <summary>
		/// Executes indirect draw or dispatch commands.
		/// </summary>
		/// <remarks>
		/// This is not supported (and will do nothing) in D3D9 and D3D10.
		/// </remarks>
		/// <param name="type">Specifies whether this is an indirect draw, indexed draw or dispatch command.</param>
		/// <param name="buffer">Buffer resource that contains command arguments.</param>
		/// <param name="offset">Offset (in bytes) from the start of the argument buffer to the first argument to use.</param>
		/// <param name="draw_count">Number of commands to execute.</param>
		/// <param name="stride">Stride (in bytes) between commands in the argument buffer.</param>
		virtual void draw_or_dispatch_indirect(indirect_command type, resource buffer, uint64_t offset, uint32_t draw_count, uint32_t stride) = 0;

		/// <summary>
		/// Copies the entire contents of the <paramref name="source"/> resource to the <paramref name="dest"/>ination resource. Dimensions of the two resources have to match.
		/// </summary>
		/// <remarks>
		/// The <paramref name="source"/> resource has to be in the <see cref="resource_usage::copy_source"/> state.
		/// The <paramref name="dest"/>ination resource has to be in the <see cref="resource_usage::copy_dest"/> state.
		/// </remarks>
		/// <param name="source">Resource to copy from.</param>
		/// <param name="dest">Resource to copy to.</param>
		virtual void copy_resource(resource source, resource dest) = 0;
		/// <summary>
		/// Copies a linear memory region from the <paramref name="source"/> buffer to the <paramref name="dest"/>ination buffer.
		/// </summary>
		/// <remarks>
		/// This is not supported (and will do nothing) in D3D9.
		/// The <paramref name="source"/> resource has to be in the <see cref="resource_usage::copy_source"/> state.
		/// The <paramref name="dest"/>ination resource has to be in the <see cref="resource_usage::copy_dest"/> state.
		/// </remarks>
		/// <param name="source">Buffer resource to copy from.</param>
		/// <param name="source_offset">Offset (in bytes) into the <paramref name="source"/> buffer to start copying at.</param>
		/// <param name="dest">Buffer resource to copy to.</param>
		/// <param name="dest_offset">Offset (in bytes) into the <paramref name="dest"/>ination buffer to start copying to.</param>
		/// <param name="size">Number of bytes to copy.</param>
		virtual void copy_buffer_region(resource source, uint64_t source_offset, resource dest, uint64_t dest_offset, uint64_t size) = 0;
		/// <summary>
		/// Copies a texture region from the <paramref name="source"/> buffer to the <paramref name="dest"/>ination texture.
		/// </summary>
		/// <remarks>
		/// The <paramref name="source"/> resource has to be in the <see cref="resource_usage::copy_source"/> state.
		/// The <paramref name="dest"/>ination resource has to be in the <see cref="resource_usage::copy_dest"/> state.
		/// </remarks>
		/// <param name="source">Buffer resource to copy from.</param>
		/// <param name="source_offset">Offset (in bytes) into the <paramref name="source"/> buffer to start copying at.</param>
		/// <param name="row_length">Number of pixels from one row to the next (in the buffer), or zero if data is tightly packed.</param>
		/// <param name="slice_height">Number of rows from one slice to the next (in the buffer) or zero if data is tightly packed.</param>
		/// <param name="dest">Texture resource to copy to.</param>
		/// <param name="dest_subresource">Index of the subresource of the <paramref name="dest"/>ination texture to copy to.</param>
		/// <param name="dest_box">A 3D box (or <see langword="nullptr"/> to reference the entire subresource) that defines the region in the <paramref name="dest"/>ination texture to copy to, in the format <c>{ left, top, front, right, bottom, back }</c>.</param>
		virtual void copy_buffer_to_texture(resource source, uint64_t source_offset, uint32_t row_length, uint32_t slice_height, resource dest, uint32_t dest_subresource, const int32_t dest_box[6] = nullptr) = 0;
		/// <summary>
		/// Copies or blits a texture region from the <paramref name="source"/> texture to the <paramref name="dest"/>ination texture.
		/// </summary>
		/// <remarks>
		/// The <paramref name="source"/> resource has to be in the <see cref="resource_usage::copy_source"/> state.
		/// The <paramref name="dest"/>ination resource has to be in the <see cref="resource_usage::copy_dest"/> state.
		/// </remarks>
		/// <param name="source">Texture resource to copy from.</param>
		/// <param name="source_subresource">Index of the subresource of the <paramref name="source"/> texture to copy from.</param>
		/// <param name="source_box">A 3D box (or <see langword="nullptr"/> to reference the entire subresource) that defines the region in the <paramref name="source"/> texture to blit from, in the format <c>{ left, top, front, right, bottom, back }</c>.</param>
		/// <param name="dest">Texture resource to copy to.</param>
		/// <param name="dest_subresource">Index of the subresource of the <paramref name="dest"/>ination texture to copy to.</param>
		/// <param name="dest_box">A 3D box (or <see langword="nullptr"/> to reference the entire subresource) that defines the region in the <paramref name="dest"/>ination texture to blit to, in the format <c>{ left, top, front, right, bottom, back }</c>.</param>
		/// <param name="filter">Filter to apply when copy requires scaling.</param>
		virtual void copy_texture_region(resource source, uint32_t source_subresource, const int32_t source_box[6], resource dest, uint32_t dest_subresource, const int32_t dest_box[6], filter_mode filter = filter_mode::min_mag_mip_point) = 0;
		/// <summary>
		/// Copies a texture region from the <paramref name="source"/> texture to the <paramref name="dest"/>ination buffer.
		/// </summary>
		/// <remarks>
		/// The <paramref name="source"/> resource has to be in the <see cref="resource_usage::copy_source"/> state.
		/// The <paramref name="dest"/>ination resource has to be in the <see cref="resource_usage::copy_dest"/> state.
		/// </remarks>
		/// <param name="source">Texture resource to copy from.</param>
		/// <param name="source_subresource">Index of the subresource of the <paramref name="source"/> texture to copy from.</param>
		/// <param name="source_box">A 3D box (or <see langword="nullptr"/> to reference the entire subresource) that defines the region in the <paramref name="source"/> texture to copy from, in the format <c>{ left, top, front, right, bottom, back }</c>.</param>
		/// <param name="dest">Buffer resource to copy to.</param>
		/// <param name="dest_offset">Offset (in bytes) into the <paramref name="dest"/>ination buffer to start copying to.</param>
		/// <param name="row_length">Number of pixels from one row to the next (in the buffer), or zero if data is tightly packed.</param>
		/// <param name="slice_height">Number of rows from one slice to the next (in the buffer), or zero if data is tightly packed.</param>
		virtual void copy_texture_to_buffer(resource source, uint32_t source_subresource, const int32_t source_box[6], resource dest, uint64_t dest_offset, uint32_t row_length = 0, uint32_t slice_height = 0) = 0;
		/// <summary>
		/// Copies a region from the multisampled <paramref name="source"/> texture to the non-multisampled <paramref name="dest"/>ination texture.
		/// </summary>
		/// <remarks>
		/// The <paramref name="source"/> resource has to be in the <see cref="resource_usage::resolve_source"/> state.
		/// The <paramref name="dest"/>ination resource has to be in the <see cref="resource_usage::resolve_dest"/> state.
		/// </remarks>
		/// <param name="source">Texture resource to resolve from.</param>
		/// <param name="source_subresource">Index of the subresource of the <paramref name="source"/> texture to resolve from.</param>
		/// <param name="source_box">A 2D rectangle (or <see langword="nullptr"/> to reference the entire subresource) that defines the region in the <paramref name="source"/> texture to resolve, in the format <c>{ left, top, front, right, bottom, back }</c>. In D3D10 and D3D11 this has to be <see langword="nullptr"/>.</param>
		/// <param name="dest">Texture resource to resolve to.</param>
		/// <param name="dest_subresource">Index of the subresource of the <paramref name="dest"/>ination texture to resolve to.</param>
		/// <param name="dest_offset">Offset (in texels) that defines the region in the <paramref name="dest"/>ination texture to resolve to, in the format <c>{ left, top, front }</c>. In D3D10 and D3D11 this has to be <see langword="nullptr"/>.</param>
		/// <param name="format">Format of the resource data.</param>
		virtual void resolve_texture_region(resource source, uint32_t source_subresource, const int32_t source_box[6], resource dest, uint32_t dest_subresource, const int32_t dest_offset[3], format format) = 0;

		/// <summary>
		/// Clears all attachments of the current render pass. Can only be called between <see cref="begin_render_pass"/> and <see cref="end_render_pass"/>.
		/// </summary>
		/// <param name="clear_flags">Combination of flags to identify which attachment types to clear.</param>
		/// <param name="color">Value to clear render targets with. Only used if <paramref name="clear_flags"/> contains <see cref="attachment_type::color"/>.</param>
		/// <param name="depth">Value to clear the depth buffer with. Only used if <paramref name="clear_flags"/> contains <see cref="attachment_type::depth"/>.</param>
		/// <param name="stencil">Value to clear the stencil buffer with. Only used if <paramref name="clear_flags"/> contains <see cref="attachment_type::stencil"/>.</param>
		/// <param name="rect_count">Number of rectangles to clear in the attachment resources, or zero to clear the whole resources.</param>
		/// <param name="rects">Pointer to an array of rectangles, in the format <c>{ left, top, right, bottom }</c>.</param>
		virtual void clear_attachments(attachment_type clear_flags, const float color[4], float depth, uint8_t stencil, uint32_t rect_count = 0, const int32_t *rects = nullptr) = 0;
		/// <summary>
		/// Clears the resource referenced by the depth-stencil view.
		/// </summary>
		/// <remarks>
		/// The resource the depth-stencil view points to has to be in the <see cref="resource_usage::depth_stencil_write"/> state.
		/// </remarks>
		/// <param name="dsv">Resource view handle of the depth-stencil.</param>
		/// <param name="clear_flags">Can be <see cref="attachment_type::depth"/> or <see cref="attachment_type::stencil"/> or both.</param>
		/// <param name="depth">Value to clear the depth buffer with. Only used if <paramref name="clear_flags"/> contains <see cref="attachment_type::depth"/>.</param>
		/// <param name="stencil">Value to clear the stencil buffer with. Only used if <paramref name="clear_flags"/> contains <see cref="attachment_type::stencil"/>.</param>
		/// <param name="rect_count">Number of rectangles to clear in the depth-stencil resource, or zero to clear the whole resource.</param>
		/// <param name="rects">Pointer to an array of rectangles, in the format <c>{ left, top, right, bottom }</c>.</param>
		virtual void clear_depth_stencil_view(resource_view dsv, attachment_type clear_flags, float depth, uint8_t stencil, uint32_t rect_count = 0, const int32_t *rects = nullptr) = 0;
		/// <summary>
		/// Clears the resource referenced by the render target view.
		/// </summary>
		/// <remarks>
		/// The resource the render target view points to has to be in the <see cref="resource_usage::render_target"/> state.
		/// </remarks>
		/// <param name="rtv">Resource view handle of the render target.</param>
		/// <param name="color">Value to clear the resource with.</param>
		/// <param name="rect_count">Number of rectangles to clear in the render target resource, or zero to clear the whole resource.</param>
		/// <param name="rects">Pointer to an array of rectangles, in the format <c>{ left, top, right, bottom }</c>.</param>
		virtual void clear_render_target_view(resource_view rtv, const float color[4], uint32_t rect_count = 0, const int32_t *rects = nullptr) = 0;
		/// <summary>
		/// Clears the resource referenced by the unordered access view.
		/// </summary>
		/// <remarks>
		/// The resource the unordered access view points to has to be in the <see cref="resource_usage::unordered_access"/> state.
		/// </remarks>
		/// <param name="uav">Resource view handle of the unordered access view.</param>
		/// <param name="values">Value to clear the resource with.</param>
		/// <param name="rect_count">Number of rectangles to clear in the unordered access resource, or zero to clear the whole resource.</param>
		/// <param name="rects">Pointer to an array of rectangles, in the format <c>{ left, top, right, bottom }</c>.</param>
		virtual void clear_unordered_access_view_uint(resource_view uav, const uint32_t values[4], uint32_t rect_count = 0, const int32_t *rects = nullptr) = 0;
		/// <summary>
		/// Clears the resource referenced by the unordered access view.
		/// </summary>
		/// <remarks>
		/// The resource the unordered access view points to has to be in the <see cref="resource_usage::unordered_access"/> state.
		/// </remarks>
		/// <param name="uav">Resource view handle of the unordered access view.</param>
		/// <param name="values">Value to clear the resource with.</param>
		/// <param name="rect_count">Number of rectangles to clear in the unordered access resource, or zero to clear the whole resource.</param>
		/// <param name="rects">Pointer to an array of rectangles, in the format <c>{ left, top, right, bottom }</c>.</param>
		virtual void clear_unordered_access_view_float(resource_view uav, const   float values[4], uint32_t rect_count = 0, const int32_t *rects = nullptr) = 0;

		/// <summary>
		/// Generates the lower mipmap levels for the specified shader resource view.
		/// Uses the largest mipmap level of the view to recursively generate the lower levels of the mip and stops with the smallest level that is specified by the view.
		/// </summary>
		/// <remarks>
		/// This will invalidate all previous descriptor bindings, which will need to be reset by calls to <see cref="bind_descriptor_set"/> or <see cref="push_descriptors"/>.
		/// The resource the shader resource view points to has to be in the <see cref="resource_usage::shader_resource"/> state and has to have been created with the <see cref="resource_flags::generate_mipmaps"/> flag.
		/// </remarks>
		/// <param name="srv">The shader resource view to update.</param>
		virtual void generate_mipmaps(resource_view srv) = 0;

		/// <summary>
		/// Begins a query.
		/// </summary>
		/// <param name="pool">Query pool that will manage the results of the query.</param>
		/// <param name="type">Type of the query to begin.</param>
		/// <param name="index">Index of the query in the pool.</param>
		virtual void begin_query(query_pool pool, query_type type, uint32_t index) = 0;
		/// <summary>
		/// Ends a query.
		/// </summary>
		/// <param name="pool">Query pool that will manage the results of the query.</param>
		/// <param name="type">Type of the query end.</param>
		/// <param name="index">Index of the query in the pool.</param>
		virtual void end_query(query_pool pool, query_type type, uint32_t index) = 0;
		/// <summary>
		/// Copy the results of queries in a query pool to a buffer resource.
		/// </summary>
		/// <remarks>
		/// The <paramref name="dest"/>ination resource has to be in the <see cref="resource_usage::copy_dest"/> state.
		/// </remarks>
		/// <param name="pool">Query pool that manages the results of the queries.</param>
		/// <param name="type">Type of the queries to copy.</param>
		/// <param name="first">Index of the first query in the pool to copy the result from.</param>
		/// <param name="count">Number of query results to copy.</param>
		/// <param name="dest">Buffer resource to copy to.</param>
		/// <param name="dest_offset">Offset (in bytes) into the <paramref name="dest"/>ination buffer to start copying to.</param>
		/// <param name="stride">Size (in bytes) of each result element.</param>
		virtual void copy_query_pool_results(query_pool pool, query_type type, uint32_t first, uint32_t count, resource dest, uint64_t dest_offset, uint32_t stride) = 0;

		/// <summary>
		/// Opens a debug event region in the command list.
		/// </summary>
		/// <param name="label">Null-terminated string containing the label of the event.</param>
		/// <param name="color">Optional RGBA color value associated with the event.</param>
		virtual void begin_debug_event(const char *label, const float color[4] = nullptr) = 0;
		/// <summary>
		/// Closes the current debug event region (the last one opened with <see cref="begin_debug_event"/>).
		/// </summary>
		virtual void end_debug_event() = 0;
		/// <summary>
		/// Inserts a debug marker into the command list.
		/// </summary>
		/// <param name="label">Null-terminated string containing the label of the debug marker.</param>
		/// <param name="color">Optional RGBA color value associated with the debug marker.</param>
		virtual void insert_debug_marker(const char *label, const float color[4] = nullptr) = 0;
	};

	/// <summary>
	/// A command queue, used to execute command lists on the GPU.
	/// <para>Functionally equivalent to the immediate 'ID3D11DeviceContext' or a 'ID3D12CommandQueue' or 'VkQueue'.</para>
	/// </summary>
	/// <remarks>
	/// This class may NOT be used concurrently from multiple threads!
	/// </remarks>
	class __declspec(novtable) command_queue : public device_object
	{
	public:
		/// <summary>
		/// Gets a special command list, on which all issued commands are executed as soon as possible (or right before the application executes its next command list on this queue).
		/// </summary>
		virtual command_list *get_immediate_command_list() = 0;

		/// <summary>
		/// Flushes and executes the special immediate command list returned by <see cref="get_immediate_command_list"/> immediately.
		/// This can be used to force commands to execute right away instead of waiting for the runtime to flush it automatically at some point.
		/// </summary>
		virtual void flush_immediate_command_list() const  = 0;

		/// <summary>
		/// Waits for all issued GPU operations on this queue to finish before returning.
		/// This can be used to ensure that e.g. resources are no longer in use on the GPU before destroying them.
		/// </summary>
		/// <remarks>
		/// Must not be called while another thread is recording to the immediate command list!
		/// </remarks>
		virtual void wait_idle() const = 0;

		/// <summary>
		/// Opens a debug event region in the command queue.
		/// </summary>
		/// <param name="label">Null-terminated string containing the label of the event.</param>
		/// <param name="color">Optional RGBA color value associated with the event.</param>
		virtual void begin_debug_event(const char *label, const float color[4] = nullptr) = 0;
		/// <summary>
		/// Closes the current debug event region (the last one opened with <see cref="begin_debug_event"/>).
		/// </summary>
		virtual void end_debug_event() = 0;
		/// <summary>
		/// Inserts a debug marker into the command queue.
		/// </summary>
		/// <param name="label">Null-terminated string containing the label of the debug marker.</param>
		/// <param name="color">Optional RGBA color value associated with the debug marker.</param>
		virtual void insert_debug_marker(const char *label, const float color[4] = nullptr) = 0;
	};
} }